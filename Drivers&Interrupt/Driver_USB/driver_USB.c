#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/usb.h>

/*

This macro is used to tell the driver to use old method or new method.

->	If it is 0, then driver will use old method. ie __init and __exit
->	If it is non zero, then driver will use new method. ie: module_usb_driver

*/

#define IS_NEW_METHOD_USED	(1)

#define USB_VENDOR_ID		(0x22d9)
#define USB_PRODUCT_ID		(0x2764)

#define PRINT_USB_INTERFACE_DESCRIPTOR(i)				\
{									\
	pr_info("USB INTERFACE DESCRIPTOR:\n");				\
	pr_info("-------------------------\n");				\
	pr_info("bLength: 0x%x\n",i.bLength);				\
	pr_info("bDescriptorType: 0x%x\n",i.bDescriptorType);		\
	pr_info("bAlternateSetting: 0x%x\n",i.bAlternateSetting);	\
	pr_info("bNumEndpoints: 0x%x\n",i.bNumEndpoints);		\
	pr_info("bInterfaceClass: 0x%x\n",i.bInterfaceClass);		\
	pr_info("bInterfaceSubClass: 0x%x\n",i.bInterfaceSubClass);	\
	pr_info("bInterfaceProtocol: 0x%x\n",i.bInterfaceProtocol);	\
	pr_info("bInterface: 0x%x\n",i.iInterface);			\
 	pr_info("\n");							\	
}

#define PRINT_USB_ENDPOINT_DESCRIPTOR(e)				\
{									\
	pr_info("USB ENDPOINT DESCRIPTOR:\n");				\
	pr_info("-------------------------\n");				\
	pr_info("bLength: 0x%x\n",e.bLength);				\
	pr_info("bDescriptorType: 0x%x\n",e.bDescriptorType);		\
	pr_info("bEndPointAddress: 0x%x\n",e.bEndpointAddress);		\
	pr_info("bmAttributes: 0x%x\n",e.bmAttributes);			\
	pr_info("wMaxPacketSize: 0x%x\n",e.wMaxPacketSize);		\
	pr_info("bInterval: 0x%x\n",e.bInterval);			\
 	pr_info("\n");							\	
}					

static int W_usb_probe(struct usb_interface *interface, const struct usb_device_id *id){
  
  unsigned int i;
  unsigned int end_points_count;
  struct usb_host_interface *iface_desc = interface->cur_altsetting;
  
  dev_info(&interface->dev,"USB Driver Probed: vendor ID: 0x%02x,\t"
		"product ID: 0x%02x\n",id->idVendor,id->idProduct);
  end_points_count = iface_desc->desc.bNumEndpoints;
  
  PRINT_USB_INTERFACE_DESCRIPTOR(iface_desc->desc);

  for(i=0; i<end_points_count; i++){
      PRINT_USB_ENDPOINT_DESCRIPTOR(iface_desc->endpoint[i].desc);
  }
  return 0;
}

static void W_usb_desconnect(struct usb_interface *interface){
	dev_info(&interface->dev,"USB Driver Desconected\n");
}

const struct usb_device_id W_usb_table[] = {
   {USB_DEVICE(USB_VENDOR_ID, USB_PRODUCT_ID)},
   {}
};

MODULE_DEVICE_TABLE(usb,W_usb_table);

static struct usb_driver W_usb_driver = {
  .name		= "William USB Driver",
  .probe	= W_usb_probe,
  .disconnect	= W_usb_desconnect,
  .id_table	= W_usb_table,
};

#if (IS_NEW_METHOD_USED == 0)
  module_usb_driver(W_usb_driver);
#else

static int __init W_usb_init(void){
   return usb_register(&W_usb_driver);
}

static void __exit W_usb_exit(void){
   usb_deregister(&W_usb_driver);
}

module_init(W_usb_init);
module_exit(W_usb_exit);
#endif

MODULE_LICENSE("GPL");
MODULE_AUTHOR("William Sanchez");
MODULE_DESCRIPTION("A simple module to implementer a driver");
MODULE_VERSION("1:1.0");
