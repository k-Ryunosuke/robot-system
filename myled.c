#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/uaccess.h>
#include<linux/io.h>
#include<linux/gpio.h>
#include<linux/i2c.h>
#include<linux/delay.h>

MODULE_AUTHOR("Ryunosuke Kamioka and Ryuichi Ueda");
MODULE_DESCRIPTION("driver for LED control");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.1");

static dev_t dev;
static struct cdev cdv;
static struct class *cls = NULL;
static volatile u32 *gpio_base = NULL;
static int led_array[4] = {25,4,12,16};
static int led_on_array[4] = {25,12,4,16};
static int led[4] = {12,16,25,4};
static int gpio_num[4] = {10,10,7,7};
static int count=0;

static void led_on(void){
        for(count=0;count<4;count++){
                gpio_base[7] = 1 << led_on_array[count];
                mdelay(100);
                gpio_base[10] = 1 << led_on_array[count];
                mdelay(100);
        }
}

static void all_off(void){
        for(count=0;count<4;count++){
                gpio_base[7] = 1 << led_on_array[count];
        }
}

static void all_on(void){
        for(count=0;count<4;count++){
                gpio_base[10] = 1 << led_on_array[count];
        }
}


static ssize_t led_write(struct file* filp, const char* buf, size_t count, loff_t* pos){
        char c;
        int i;

        if(copy_from_user(&c,buf,sizeof(char))) return -EFAULT;

        if(c == '0'){
                gpio_base[10] = 1 <<25;
        }else if(c=='1'){
                led_on();
        }else if(c=='2'){
                for(i=0;i<2;i++){
                        led_on();
                }
        }else if(c=='3'){
                for(i=0;i<3;i++){
                        led_on();
                }
        }else if(c=='4'){
                for(i=0;i<4;i++){
                        led_on();
                }
        }else if(c == '5'){
                for(i=0;i<4;i++){
                        for(count=0;count<4;count++){
                                gpio_base[7] = 1 << led_on_array[count];
                                mdelay(200-i*40);
                                gpio_base[10] = 1 << led_on_array[count];
                                mdelay(200-i*40);
                        }
                        for(count=1;count<3;count++){
                                gpio_base[7] = 1 << led_array[count];
                                mdelay(200-40*i);
                                gpio_base[10] = 1 << led_array[count];
                                mdelay(200-40*i);           
                        }
                }
                all_off();
                for(i=0;i<15;i++){
                        for(count=0;count<4;count++){
                                gpio_base[gpio_num[count]] = 1 << led_array[count];
                                mdelay(50);
                        }
                        for(count=0;count<4;count++){
                                gpio_base[gpio_num[count]] = 1 << led[count];
                                mdelay(50);
                        }
                }
                all_on();
                for(i=0;i<15;i++){
                        all_off();
                        mdelay(30);
                        all_on();
                        mdelay(100);
                }
                mdelay(1000);
                all_off();
                mdelay(3000);
                all_on();
        }
        return 1;
}

static struct file_operations led_fops ={
        .owner = THIS_MODULE,
        .write = led_write,
};

static int __init init_mod(void){
        int retval,i;
        retval = alloc_chrdev_region(&dev, 0, 1, "myled");
        if(retval < 0){
                printk(KERN_ERR "chrdev_add failed. major:%d.\n minor:%d.\n",MAJOR(dev),MINOR(dev));
                return retval;
        }
        printk(KERN_INFO "%s is loaded major:%d\n", __FILE__, MAJOR(dev));
        cdev_init(&cdv, &led_fops);
        retval = cdev_add(&cdv, dev, 1);

        if(retval < 0){
                printk(KERN_ERR "cdev_add failed. major:%d.\n minor:%d.\n",MAJOR(dev),MINOR(dev));
                return retval;
        }

        cls = class_create(THIS_MODULE,"myled");

        if(IS_ERR(cls)){
                printk(KERN_ERR"class_create failed");
                return PTR_ERR(cls);
        }

        device_create(cls, NULL, dev,NULL, "myled%d",MINOR(dev));

        gpio_base = ioremap_nocache(0x3f200000,0xA0);

        for(i=0;i<4;i++){
                const u32 led = led_array[i];
                const u32 index = led/10;
                const u32 shift = (led%10)*3;
                const u32 mask = ~(0x7 << shift);
                gpio_base[index] = (gpio_base[index] & mask) | (0x1 << shift);
        }
        return 0;
}

static void __exit cleanup_mod(void){
        cdev_del(&cdv);
        device_destroy(cls,dev);
        class_destroy(cls);
        unregister_chrdev_region(dev,1);
}

module_init(init_mod);
module_exit(cleanup_mod);
