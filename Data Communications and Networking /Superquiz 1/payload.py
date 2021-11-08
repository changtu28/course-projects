def payload(pkt):
    """Extracts the payload out of an IPv4 packet"""
    header_len = int(format(int(bin(pkt[0])[2:], 2), "08b")[4:], 2)
    #print(header_len)
    header_len = int(header_len * 32 / 8)
    to_return = bytearray()
    for byte in pkt[header_len:]:
        to_return.append(byte)
    return to_return
    
    
def main():
    from ComposePacket import composepacket
    print(payload(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)))
    
if __name__ == "__main__":
    main()