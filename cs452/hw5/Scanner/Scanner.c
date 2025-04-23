#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

// #include "Hello_scanner.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("BSU CS 452 HW5");
MODULE_AUTHOR("<hunterbarclay@u.boisestate.edu>");

typedef struct {
  dev_t devno;
  struct cdev cdev;
  char *sep;
  unsigned long long sep_len;
} Device; /* per-init() data */

typedef struct {
  char ctl;
  char *sep;
  unsigned long long sep_len;
  char *source;
  unsigned long long source_len;
  unsigned long long head;
} File; /* per-open() data */

static Device device;

static int open(struct inode *inode, struct file *filp) {
  File *file = (File *)kmalloc(sizeof(*file), GFP_KERNEL);
  if (!file) {
    printk(KERN_ERR "%s: kmalloc() failed\n", DEVNAME);
    return -ENOMEM;
  }
  file->sep_len = device.sep_len;
  file->sep = (char *)kmalloc(device.sep_len, GFP_KERNEL);
  if (!file->sep) {
    printk(KERN_ERR "%s: kmalloc() failed\n", DEVNAME);
    return -ENOMEM;
  }
  strcpy(file->sep, device.sep);
  file->source = NULL;
  file->source_len = 0;
  file->ctl = 0;
  file->head = 0;
  filp->private_data = file;
  // testmod();
  return 0;
}

static int release(struct inode *inode, struct file *filp) {
  File *file = filp->private_data;
  if (file->sep)
    kfree(file->sep);
  if (file->source)
    kfree(file->source);
  kfree(file);
  return 0;
}

static char is_one_of(char one, const char *of, unsigned long long of_len) {
  unsigned long long i = 0;
  while (i < of_len && of[i] != one) {
    ++i;
  }
  return i < of_len;
}

static ssize_t read(struct file *filp, char *buf, size_t count, loff_t *f_pos) {
  File *file = filp->private_data;
  unsigned long long base = file->head;
  char end = 0;
  unsigned long long n;

  // If end of data, return immediately
  if (file->head > file->source_len) {
    return -1;
  }

  // Get token
  while ((file->head - base) < count && file->head < file->source_len && !end) {
    end = is_one_of(file->source[file->head], file->sep, file->sep_len);
    if (!end)
      ++file->head;
  }

  // Check for end of token
  n = file->head - base;
  if (!n) { // If token is length zero, report end of token.
    ++file->head;
    return 0;
  }

  // Copy token to buffer and return read characters
  if (copy_to_user(buf, file->source + base, n)) {
    printk(KERN_ERR "%s: copy_to_user() failed\n", DEVNAME);
    return -2;
  }
  return n;
}

static ssize_t write(struct file *filp, const char *buf, size_t count,
                     loff_t *f_pos) {
  File *file = filp->private_data;

  char **s;
  unsigned long long *s_len;
  if (file->ctl) {
    // Read in separators
    s = &file->sep;
    s_len = &file->sep_len;
    file->ctl = 0;
  } else {
    // Read in source
    s = &file->source;
    s_len = &file->source_len;
    file->head = 0;
  }
  if (*s != NULL)
  kfree(*s);
  *s_len = count;
  *s = (char *)kmalloc(count, GFP_KERNEL);

  if (copy_from_user(*s, buf, count)) {
    printk(KERN_ERR "%s: copy_from_user() failed\n", DEVNAME);
    return 0;
  }

  return count;
}

static long ioctl(struct file *filp, unsigned int cmd, unsigned long arg) {
  File *file = filp->private_data;
  if (cmd == 0) {
    file->ctl = 1;
  }
  return 0;
}

static struct file_operations ops = {.open = open,
                                     .release = release,
                                     .read = read,
                                     .write = write,
                                     .unlocked_ioctl = ioctl,
                                     .owner = THIS_MODULE};

static int __init my_init(void) {
  const char *sep = " ";
  int err;
  device.sep_len = 1;
  device.sep = (char *)kmalloc(device.sep_len, GFP_KERNEL);
  if (!device.sep) {
    printk(KERN_ERR "%s: kmalloc() failed\n", DEVNAME);
    return -ENOMEM;
  }
  strcpy(device.sep, sep);
  err = alloc_chrdev_region(&device.devno, 0, 1, DEVNAME);
  if (err < 0) {
    printk(KERN_ERR "%s: alloc_chrdev_region() failed\n", DEVNAME);
    return err;
  }
  cdev_init(&device.cdev, &ops);
  device.cdev.owner = THIS_MODULE;
  err = cdev_add(&device.cdev, device.devno, 1);
  if (err) {
    printk(KERN_ERR "%s: cdev_add() failed\n", DEVNAME);
    return err;
  }
  printk(KERN_INFO "%s: init\n", DEVNAME);
  return 0;
}

static void __exit my_exit(void) {
  cdev_del(&device.cdev);
  unregister_chrdev_region(device.devno, 1);
  kfree(device.sep);
  printk(KERN_INFO "%s: exit\n", DEVNAME);
}

module_init(my_init);
module_exit(my_exit);
