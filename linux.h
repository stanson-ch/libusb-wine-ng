#ifndef __LINUX_H__
#define __LINUX_H__

#include <unistd.h>
#include <stdint.h>
#include <sys/stat.h>

struct usb_ctrltransfer {
	/* keep in sync with usbdevice_fs.h:usbdevfs_ctrltransfer */
	uint8_t  bRequestType;
	uint8_t  bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;

	uint32_t timeout;	/* in milliseconds */

	/* pointer to data */
	void *data;
};

struct usb_bulktransfer {
	/* keep in sync with usbdevice_fs.h:usbdevfs_bulktransfer */
	unsigned int ep;
	unsigned int len;
	unsigned int timeout;	/* in milliseconds */

	/* pointer to data */
	void *data;
};

struct usb_setinterface {
	/* keep in sync with usbdevice_fs.h:usbdevfs_setinterface */
	unsigned int interface;
	unsigned int altsetting;
};

#define USB_MAXDRIVERNAME 255

struct usb_getdriver {
	unsigned int interface;
	char driver[USB_MAXDRIVERNAME + 1];
};

#define USB_URB_DISABLE_SPD	1
#define USB_URB_ISO_ASAP	2
#define USB_URB_QUEUE_BULK	0x10

#define USB_URB_TYPE_ISO	0
#define USB_URB_TYPE_INTERRUPT	1
#define USB_URB_TYPE_CONTROL	2
#define USB_URB_TYPE_BULK	3

struct usb_iso_packet_desc {
	unsigned int length;
	unsigned int actual_length;
	unsigned int status;
};

struct usb_urb {
	unsigned char type;
	unsigned char endpoint;
	int status;
	unsigned int flags;
	void *buffer;
	int buffer_length;
	int actual_length;
	int start_frame;
	int number_of_packets;
	int error_count;
	unsigned int signr;  /* signal to be sent on error, -1 if none should be sent */
	void *usercontext;
	struct usb_iso_packet_desc iso_frame_desc[0];
};

struct usb_connectinfo {
	unsigned int devnum;
	unsigned char slow;
};

struct usb_ioctl {
	int ifno;	/* interface 0..N ; negative numbers reserved */
	int ioctl_code;	/* MUST encode size + direction of data so the
			 * macros in <asm/ioctl.h> give correct values */
	void *data;	/* param buffer (in, or out) */
};

struct usb_ioctl_32 {
	int ifno;	/* interface 0..N ; negative numbers reserved */
	int ioctl_code;	/* MUST encode size + direction of data so the
			 * macros in <asm/ioctl.h> give correct values */
	uint32_t data;	/* param buffer (in, or out) */
};

struct usb_hub_portinfo {
	unsigned char numports;
	unsigned char port[127];	/* port to device num mapping */
};

#define X_IOCTL_USB_CONTROL		0
#define X_IOCTL_USB_BULK		2
#define X_IOCTL_USB_RESETEP		3
#define X_IOCTL_USB_SETINTF		4
#define X_IOCTL_USB_SETCONFIG		5
#define X_IOCTL_USB_GETDRIVER		8
#define X_IOCTL_USB_SUBMITURB		10
#define X_IOCTL_USB_DISCARDURB		11
#define X_IOCTL_USB_REAPURB		12
#define X_IOCTL_USB_REAPURBNDELAY	13
#define X_IOCTL_USB_CLAIMINTF		15
#define X_IOCTL_USB_RELEASEINTF		16
#define X_IOCTL_USB_CONNECTINFO		17
#define X_IOCTL_USB_IOCTL		18
#define X_IOCTL_USB_HUB_PORTINFO	19
#define X_IOCTL_USB_RESET		20
#define X_IOCTL_USB_CLEAR_HALT		21
#define X_IOCTL_USB_DISCONNECT		22
#define X_IOCTL_USB_CONNECT		23

/*
 * IOCTL_USB_HUB_PORTINFO, IOCTL_USB_DISCONNECT and IOCTL_USB_CONNECT
 * all work via IOCTL_USB_IOCTL
 */

#endif

