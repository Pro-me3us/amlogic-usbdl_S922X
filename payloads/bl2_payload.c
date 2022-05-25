/*
 * mini payload to be merged with Bl2 payload, jumps 0x1000 header and clears USB state 
 */
#define _clear_icache() ((void (*)(void))0xffff0534)()   //s905d3 - 0xffff048c
#define _dwc_pcd_irq() ((void (*)(void))0xffff6d7c)()    //s905d3 - 0xffff8250
#define _jmp_bl2() ((void (*)(void))0xfffa1000)()
void _start()
{
    _clear_icache(); //clear instruction cache
    _dwc_pcd_irq();  //clear USB state
    _dwc_pcd_irq();  //after exploitation
    _jmp_bl2();      //jump to BL2 entrypoint
}
