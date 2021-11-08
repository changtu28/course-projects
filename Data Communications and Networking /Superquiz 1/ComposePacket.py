import struct

def composepacket (version, hdrlen, tosdscp, totallength, identification, flags, fragmentoffset, timetolive, protocoltype, headerchecksum, sourceaddress, destinationaddress):
    """Composes the IPv4 header for a packet using byte arrays"""
    all_info = [version, hdrlen, tosdscp, totallength, identification, flags, 
                fragmentoffset, timetolive, protocoltype, headerchecksum, 
                sourceaddress, destinationaddress]   
    valid_bit_size = [4, 4, 6, 16, 16, 3, 13, 8, 8, 16, 32, 32]
    error_code = 1
    
    if version != 4:
        return error_code
    else:
        error_code += 1
        all_info[0] = bin(version)
    
    for i in range(1, len(all_info)):
        #all_info[i] = bin(all_info[i])
        if all_info[i].bit_length() > valid_bit_size[i] or all_info[i] < 0:
           #print(all_info[i], valid_bit_size[i])
            return error_code
        else:
            error_code += 1
    
    packet = bytearray(20)
    
    #Version & HdrLen
    packet[0] = int((format(version, '04b') + format(hdrlen, '04b')), 2)
    #TOS / DiffServ CP & 2 Unused
    packet[1] = int(format(tosdscp, '06b') , 2) << 2
    #Total Length
    totalLen_bin = format(totallength, '016b')
    packet[2] = int(totalLen_bin[:8], 2)
    packet[3] = int(totalLen_bin[8:], 2)
    #Identification
    id_bin = format(identification, '016b')
    packet[4] = int(id_bin[:8], 2)
    packet[5] = int(id_bin[8:], 2)
    #Flags & Fragment Offset
    flags_bin = format(flags, '03b')
    fragOffset_bin = format(fragmentoffset, '013b')
    packet[6] = int((flags_bin + fragOffset_bin[:5]), 2)
    packet[7] = int(fragOffset_bin[5:], 2)
    #Time-to-Live
    packet[8] = int(format(timetolive, '08b'), 2)
    #Protocol Type
    packet[9] = int(format(protocoltype, '08b'), 2)
    #Header Checksum
    headerCheck_bin = format(headerchecksum, '016b')
    packet[10] = int(headerCheck_bin[:8], 2)
    packet[11] = int(headerCheck_bin[8:], 2)    
    #Source Address
    sourceAddress_bin = format(sourceaddress, '032b')
    packet[12] = int(sourceAddress_bin[:8], 2)
    packet[13] = int(sourceAddress_bin[8:16], 2)
    packet[14] = int(sourceAddress_bin[16:24], 2)
    packet[15] = int(sourceAddress_bin[24:], 2)
    #Destination Address
    destAddress_bin = format(destinationaddress, '032b')
    packet[16] = int(destAddress_bin[:8], 2)
    packet[17] = int(destAddress_bin[8:16], 2)
    packet[18] = int(destAddress_bin[16:24], 2)
    packet[19] = int(destAddress_bin[24:], 2)
    
    return packet

#print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[18])

def main():
    print(composepacket(5,5,0,4000,24200,0,63,22,6,4711, 2190815565, 3232270145) == 1)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[18] == 135)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[19] == 65)
    print(composepacket(4,16,0,4000,24200,0,63,22,6,4711, 2190815565, 3232270145) == 2)
    print(composepacket(4,15,64,4000,24200,0,63,22,6,4711, 2190815565, 3232270145) == 3)
    print(composepacket(4,15,63,65536,24200,0,63,22,6,4711, 2190815565, 3232270145) ==4)
    print(composepacket(4,15,63,65535,65536,0,63,22,6,4711, 2190815565, 3232270145) == 5)
    print(composepacket(4,15,63,65535,65535,8,63,22,6,4711, 2190815565, 3232270145) == 6)
    print(composepacket(4,15,63,65535,65535,7,8192,22,6,4711, 2190815565, 3232270145) == 7)
    print(composepacket(4,15,63,65535,65535,7,8191,256,6,4711, 2190815565, 3232270145) == 8)
    print(composepacket(4,15,63,65535,65535,7,8191,255,256,4711, 2190815565, 3232270145) == 9)
    print(composepacket(4,15,63,65535,65535,7,8191,255,255,65536, 2190815565, 3232270145) == 10)
    print(composepacket(4,15,63,65535,65535,7,8191,255,255,65535, 4294967296, 3232270145) == 11)
    print(composepacket(4,15,63,65535,65535,7,8191,255,255,65535, 4294967295, 4294967296) == 12)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[0] == 69)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[1] == 0)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[2] == 5)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[3] == 220)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[4] == 94)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[5] == 136)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[6] == 0)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[7] == 63)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[8] == 22)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[9] == 6)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[10] == 18)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[11] == 103)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[12] == 130)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[13] == 149)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[14] == 49)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[15] == 77)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[16] == 192)
    print(composepacket(4,5,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145)[17] == 168)
    print(composepacket(4,-3,0,1500,24200,0,63,22,6,4711, 2190815565, 3232270145) == 2)

if __name__ == "__main__":
    main()