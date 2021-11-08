def destaddress (pkt):
    """Extracts the IPv4 destination address from the recieved packet and
    returns a pair (a, dd) where a is the 32-bit value of the address and dd
    is a string showing the address (ie. xxx.xxx.xxx.xxx)"""
    bit1 = pkt[16]
    bit2 = pkt[17]
    bit3 = pkt[18]
    bit4 = pkt[19]
    #32 bit address
    address = (pkt[16] << 24) | (pkt[17] << 16) | (pkt[18] << 8) | pkt[19]#, 2)
    
    #Dotted-decimal notation address
    dotted_decimal = str(pkt[16]) + "." + str(pkt[17]) + "." + str(pkt[18]) + "." + str(pkt[19])
    
    return address, dotted_decimal
    
    
def main():
    from ComposePacket import composepacket
    print(destaddress(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)))
    
if __name__ == "__main__":
    main()