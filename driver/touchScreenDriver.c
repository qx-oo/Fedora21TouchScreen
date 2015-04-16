#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/usb/input.h>
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Qx-oo TouchScreen Driver");
MODULE_AUTHOR("qx oo <q-x64@live.com>");

#define USB_TOUCHSCREEN_VENDOR_ID 0x0eef
#define USB_TOUCHSCREEN_PRODUCT_ID 0x0001

static struct usb_device_id usb_tchsr_table [] = {
    { USB_DEVICE(USB_TOUCHSCREEN_VENDOR_ID, USB_TOUCHSCREEN_PRODUCT_ID) },
    { }
};
MODULE_DEVICE_TABLE(usb,usb_tchsr_table);


//定义usb结构
struct usb_tchsr_dev{
	char name[128];//触摸屏设备名称
	char phys[64];//设备之节点
	struct usb_device *udev;//描述usb设备结构体
	struct input_dev *ipdev;//usb输入设备
	struct urb *irq;//usb中断请求
	dma_addr_t data_dma; //传输用的地址
	struct usb_interface *interface;
	signed char* data;
	int pressure;
	int x;
	int y;
};
//声明
static int usb_tchsr_probe(struct usb_interface *inf,
                const struct usb_device_id *id);
static void usb_tchsr_disconnect(struct usb_interface *inf);
static int usb_tchsr_event(struct input_dev *dev,unsigned int type,
                        unsigned int code, int value);
//usb驱动结构
static struct usb_driver usb_tchsr_driver = {
	.name = "touchScreen",   //驱动名称
	.probe = usb_tchsr_probe, //驱动的探测函数
	.disconnect = usb_tchsr_disconnect, //断开时调用
	.id_table = usb_tchsr_table,
};
//模块加载函数
static int __init usb_tchsr_init(void)
{
	int result = usb_register(&usb_tchsr_driver);
	if(result)
		printk(KERN_ALERT"Device regist fail!\n");
	printk(KERN_ALERT"############********Device init success!\n");
	return result;
}
//模块结束函数
static void __exit usb_tchsr_exit(void)
{
	printk(KERN_ALERT"Driver is end!");
	usb_deregister(&usb_tchsr_driver);
	printk(KERN_ALERT"############********Device exit success!\n");
}


//中断处理函数
static void usb_tchsr_irq(struct urb *urb, struct pt_regs *regs)
{
	printk(KERN_ALERT"############********usb_tchsr_irq is begin!\n");
//	printk(KERN_ALERT"############********Data X : %d  , Y : %d  Touch : %d\n",tchsr->data[1],tchsr->data[2],tchsr->pressure);
	struct usb_tchsr_dev *tchsr = urb->context;
	struct input_dev *dev = tchsr->ipdev;
	int status;
	switch(urb->status){
		case 0: break;
		case -ECONNRESET:
		case -ENOENT:
		case -ESHUTDOWN:return;
		default: goto resubmit;
	}
	tchsr->x =((int)tchsr->data[1])*128 + ((int)tchsr->data[2])+100000;
	tchsr->y =((int)tchsr->data[3])*128 + ((int)tchsr->data[4])+100000;
	input_report_key(dev,BTN_TOUCH,1);//按下
	input_report_key(dev,BTN_TOUCH,0);//松开
	input_report_abs(dev, ABS_X,tchsr->x);
//	input_report_abs(dev, ABS_X,tchsr->data[2]);   
	input_report_abs(dev, ABS_Y,tchsr->y);
//	input_report_abs(dev, ABS_Y,tchsr->data[4]);
	//input_report_rel(dev, REL_WHEEL,tchsr->data[3]);
	input_report_abs(dev, ABS_PRESSURE,tchsr->data[0]);
	//
	//printk(KERN_ALERT"############********Data X : %d  , Y : %d  Touch : %d\n",tchsr->x,tchsr->y,tchsr->pressure);
	//
	printk(KERN_ALERT"####  data[1]: %c,  data[2]: %c,  data[3]: %c,  data[4]: %c\n",tchsr->data[1],tchsr->data[2],tchsr->data[3],tchsr->data[4]);
	//事件同步
	input_sync(dev);
	//处理睡眠
resubmit:
	status = usb_submit_urb(urb,GFP_ATOMIC);
	if(status)
		printk("can't resubmit intr");
}

//usb设备打开函数
static int usb_tchsr_open(struct input_dev *dev)
{
	printk(KERN_ALERT"############********usb_tchsr_open!\n");
	struct usb_tchsr_dev *tchsr = input_get_drvdata(dev);

	printk(KERN_ALERT"####tchsr's name is : %s\n",tchsr->name);
	printk(KERN_ALERT"####tchsr's phys is : %s\n",tchsr->phys);

	//tchsr->irq->dev = interface_to_usbdev(tchsr->ipdev);
	tchsr->irq->dev = tchsr->udev;
	if(usb_submit_urb(tchsr->irq,GFP_KERNEL))
		return -EIO;
	return 0;
}

//usb设备关闭函数
static void usb_tchsr_close(struct input_dev *dev)
{
	printk(KERN_ALERT"############********usb_tchsr_close!\n");
	struct usb_tchsr_dev *tchsr = input_get_drvdata(dev);
	usb_kill_urb(tchsr->irq);
}

//usb驱动探测函数
static int usb_tchsr_probe(struct usb_interface *inf,
		const struct usb_device_id *id)
{
	printk(KERN_ALERT"############********probe function start!\n");
	struct usb_device *dev = interface_to_usbdev(inf);
	struct usb_host_interface *interface;
	struct usb_endpoint_descriptor *endpoint;
	struct usb_tchsr_dev *tchsr;
	struct input_dev *input_dev;
	int pipe,maxp;

	interface = inf->cur_altsetting;//选择的interface
	if(interface->desc.bNumEndpoints != 1) //触摸屏只有一个终端in端点
		return -ENODEV;
	endpoint = &interface->endpoint[0].desc; //读取端点描述符
	if(!usb_endpoint_is_int_in(endpoint))
		return -ENODEV;
	//endpoint设置为中断端点
	printk(KERN_ALERT"############********pipe success!\n");
	pipe = usb_rcvintpipe(dev , endpoint->bEndpointAddress);
	//获取包的最大值
	printk(KERN_ALERT"############********maxp success!\n");
	maxp = usb_maxpacket(dev,pipe,usb_pipeout(pipe));
	//分配内存
	tchsr = kzalloc(sizeof(struct usb_tchsr_dev),GFP_KERNEL);

	input_dev = input_allocate_device();
	if(!tchsr || !input_dev)
		goto fail1;
	tchsr->data = usb_alloc_coherent(dev,8,GFP_ATOMIC,&tchsr->data_dma);
	if(!tchsr->data)
		goto fail1;
	//urb内存申请空间
	tchsr->irq = usb_alloc_urb(0, GFP_KERNEL);
	if (!tchsr->irq)
		goto fail2;
	tchsr->interface = inf;
	//填充usb设备结构体和输入设备结构体
	tchsr->udev = dev;
	tchsr->ipdev = input_dev;
	//获取设备的名称
	if(dev->manufacturer)
		strlcpy(tchsr->name, dev->manufacturer,sizeof(tchsr->name));
	//产品名字
	if(dev->product){
		if(dev->manufacturer)
			strlcpy(tchsr->name, "",sizeof(tchsr->name));
		strlcat(tchsr->name,dev->product,sizeof(tchsr->name));
	}
	printk(KERN_ALERT"############********Dvice name:%s!\n",tchsr->name);
	//检测不到名字
	if (!strlen(tchsr->name))
		snprintf(tchsr->name, sizeof(tchsr->name),
			"USB HIDBP TouchSreen %04x:%04x",
			le16_to_cpu(dev->descriptor.idVendor),
			le16_to_cpu(dev->descriptor.idProduct));
	//填充设备结构节点
	usb_make_path(dev,tchsr->phys,sizeof(tchsr->phys));
	strlcpy(tchsr->phys,"/input0",sizeof(tchsr->phys));
	//将设备的名称赋给设备内嵌的输入子系统结构体
	input_dev->name = tchsr->name;
	input_dev->phys = tchsr->phys;
	//input_dev 中的 input_id 结构体，用来存储厂商、设备类型和设备的编号
	usb_to_input_id(dev,&input_dev->id);
	//cdev设备类别
	input_dev->dev.parent = &inf->dev;
	//tchsr设置input的私有数据
	input_set_drvdata(input_dev,tchsr);
	//设置事件,EV_KEY按钮事件,EV_REL绝对坐标事件,REL相对坐标
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	//input_dev->evbit[0] = BIT(EV_SYN) | BIT(EV_KEY) | BIT(EV_ABS);
	//设置绝对坐标
	input_dev->absbit[0] = BIT(ABS_X) | BIT(ABS_Y);
	//input_dev->evbit[0] = BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WORD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_params(input_dev, ABS_X, 0x0, 0x7fff, 0, 0);
	input_set_abs_params(input_dev, ABS_Y, 0x0, 0x7fff, 0, 0);
	//if (type->max_press)
	input_set_abs_params(input_dev, ABS_PRESSURE, 0, 1, 0, 0);
        //设备赋值
        //input_dev->grab->private = tchsr;
	//输入设备打开函数
        input_dev->open = usb_tchsr_open;
	input_dev->close = usb_tchsr_close;
	//构建urb
	usb_fill_int_urb(tchsr->irq,dev,pipe,tchsr->data,
			(maxp > 8 ? 8: maxp), usb_tchsr_irq,
			tchsr,endpoint->bInterval);
	//指定urb需要传输的DMA缓冲区
	tchsr->irq->dev = dev;
	tchsr->irq->transfer_dma = tchsr->data_dma;
	tchsr->irq->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
	//注册输入设备
	if(input_register_device(tchsr->ipdev))
		goto fail2;
	usb_set_intfdata(inf,tchsr); 
	printk(KERN_ALERT"############********Probe is end!\n");
	return 0;
fail2:	usb_free_coherent(dev,8,tchsr->data,tchsr->data_dma);
	printk(KERN_ALERT"FAIL2\n");
fail1:	input_free_device(input_dev);
	printk(KERN_ALERT"FAIL1\n");
	kfree(tchsr);
	return -ENOMEM;
}

//断开连接函数
static void usb_tchsr_disconnect(struct usb_interface *inf)
{
	//获取设备结构体
	struct usb_tchsr_dev *tchsr = usb_get_intfdata(inf);
	//设置为NULL
	usb_set_intfdata(inf,NULL);
	if(tchsr)
	{
		usb_kill_urb(tchsr->irq);
		input_unregister_device(tchsr->ipdev);
		usb_free_urb(tchsr->irq);
		usb_free_coherent(interface_to_usbdev(inf),8, 
				tchsr->data,tchsr->data_dma);
		kfree(tchsr);
	}
	printk(KERN_ALERT"############********Device disnect!\n");
}

module_init(usb_tchsr_init);
module_exit(usb_tchsr_exit);
