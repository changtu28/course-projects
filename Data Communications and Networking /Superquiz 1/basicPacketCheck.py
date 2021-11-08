def basicpacketcheck (pkt):
    """Does some basic checks on a packet"""
    
    #Checks if packet ncludes a full IPv4 header
    if len(pkt) < 20:
        return 1
    
    #Checks if the version field = 4
    #num_bin = bin(pkt[0])
    #num_bin_stripped = num_bin[2:]
    #num_bin_8 = format(int(num_bin_stripped, 2), "08b")
    #num_bin_4 = num_bin_8[:4]
    #num = int(num_bin_4, 2)
    #print(num_bin)
    #print(num_bin_stripped)
    #print(num_bin_8)
    #print(num_bin_4)
    #print(num)
    elif int(format(int(bin(pkt[0])[2:], 2), "08b")[:4], 2) != 4:
        return 2
    
    #Checks if the head checksum is correct
    elif not checksum(pkt):
        return 3
    
    #Checks if the total packet length is correct
    #fh = pkt[2]
    #sh = pkt[3]
    #totalLength_bin = bin(fh)[2:] + bin(sh)[2:]
    #print(int(totalLength_bin, 2))
    #int(bin(pkt[2])[2:] + bin(pkt[3])[2:], 2)
    if (pkt[2] << 8) | pkt[3] != len(pkt):
        return 4
    
    else:
        return True

def checksum(pkt):
    """Checks to see if an IPv4 packet has a valid checksum"""
    X = 0
    
    index = 0
    size = 20
    while size > 1:
        X += int(str("%02x" % (pkt[index])) + str("%02x" % (pkt[index + 1])), 16)
        size -= 2
        index += 2
    
    while X > 0xFFFF:
        X0 = X & 0xFFFF
        X1 = X >> 16
        X = X0 + X1
    return X == 0xFFFF


def main():
    pkt1 = bytearray([0x45, 0x0, 0x0, 0x1e, 0x4, 0xd2, 0x0, 0x0, 0x40, 0x6, 
                      0x20, 0xb4, 0x12, 0x34, 0x56, 0x78, 0x98, 0x76, 0x54, 
                      0x32, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0])
    
    pkt2 = bytearray([0x45, 0x0, 0x0, 0x1e, 0x16, 0x2e, 0x0, 0x0, 0x40, 0x6,
                      0xcd, 0x59, 0x66, 0x66, 0x44, 0x44, 0x98, 0x76, 0x54, 
                      0x32, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0])
    
    pkt3 = bytearray([0x45, 0x0, 0x0, 0x1b, 0x12, 0x67, 0x20, 0xe, 0x20, 0x6,
                      0x35, 0x58, 0x66, 0x66, 0x44, 0x44, 0x55, 0x44, 0x33, 
                      0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0])

    print(basicpacketcheck(pkt1))
    print(basicpacketcheck(pkt2))
    print(basicpacketcheck(pkt3))
    print(basicpacketcheck(bytearray ([0x45, 0x0, 0x0, 0x1e, 0x4, 0xd2, 0x0, 0x0, 0x40, 0x6, 0x20, 0xb4, 0x12, 0x34, 0x56, 0x78, 0x98, 0x76, 0x54, 0x32, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0])))
    
if __name__ == "__main__":
    main()