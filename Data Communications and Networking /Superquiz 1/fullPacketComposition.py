def revisedcompose (hdrlen, tosdscp, identification, flags, fragmentoffset, timetolive, protocoltype, sourceaddress, destinationaddress, payload):
    """Composes a full IPv4 packet, including payload. Checks to ensure all
    header information is correct and sets version to 4. Calculates the 
    total length parameter of the header and also the header checksum"""
    version = 4
    header_length = hdrlen * 4
    totallength = header_length + len(payload)
    headerchecksum = 0
    
    
    #Error checks
    all_info = [version, hdrlen, tosdscp, totallength, identification, flags, 
                fragmentoffset, timetolive, protocoltype, headerchecksum, 
                sourceaddress, destinationaddress]   
    valid_bit_size = [4, 4, 6, 16, 16, 3, 13, 8, 8, 16, 32, 32]
    error_code = 1
    if version != 4:
        return error_code
    elif hdrlen < 5:
        return 2
    else:
        error_code += 1
        all_info[0] = bin(version)
    
    for i in range(1, len(all_info)):
        if all_info[i].bit_length() > valid_bit_size[i] or all_info[i] < 0:
            return error_code
        else:
            error_code += 1
            
    #Initializing the header
    header = bytearray(header_length)
    
    #Version & HdrLen
    header[0] = int((format(version, '04b') + format(hdrlen, '04b')), 2)
    #TOS / DiffServ CP & 2 Unused
    header[1] = int(format(tosdscp, '06b') , 2) << 2
    #Total Length
    totalLen_bin = format(totallength, '016b')
    header[2] = int(totalLen_bin[:8], 2)
    header[3] = int(totalLen_bin[8:], 2)
    #Identification
    id_bin = format(identification, '016b')
    header[4] = int(id_bin[:8], 2)
    header[5] = int(id_bin[8:], 2)
    #Flags & Fragment Offset
    flags_bin = format(flags, '03b')
    fragOffset_bin = format(fragmentoffset, '013b')
    header[6] = int((flags_bin + fragOffset_bin[:5]), 2)
    header[7] = int(fragOffset_bin[5:], 2)
    #Time-to-Live
    header[8] = int(format(timetolive, '08b'), 2)
    #Protocol Type
    header[9] = int(format(protocoltype, '08b'), 2)
    #Header Checksum
    headerCheck_bin = format(headerchecksum, '016b')
    header[10] = int(headerCheck_bin[:8], 2)
    header[11] = int(headerCheck_bin[8:], 2)    
    #Source Address
    sourceAddress_bin = format(sourceaddress, '032b')
    header[12] = int(sourceAddress_bin[:8], 2)
    header[13] = int(sourceAddress_bin[8:16], 2)
    header[14] = int(sourceAddress_bin[16:24], 2)
    header[15] = int(sourceAddress_bin[24:], 2)
    #Destination Address
    destAddress_bin = format(destinationaddress, '032b')
    header[16] = int(destAddress_bin[:8], 2)
    header[17] = int(destAddress_bin[8:16], 2)
    header[18] = int(destAddress_bin[16:24], 2)
    header[19] = int(destAddress_bin[24:], 2)
    
    
    #Get checksum
    headerchecksum = calculate_checksum(header)
    
    #Update checksum in header
    headerCheck_bin = format(headerchecksum, '016b')
    #print(headerCheck_bin)
    header[10] = int(headerCheck_bin[:8], 2)
    header[11] = int(headerCheck_bin[8:], 2)
    
    
    #Add any extra header
    #for i in range(hdrlen - 5):
    #    header.append(0)
        
        
    packet = header + payload
    return packet
        
    
def calculate_checksum(header):
    """Calcualtes the checksum for a IPv4 header"""
    X = 0
    
    index = 0
    size = 20
    while size > 1:
        X += int(str("%02x" % (header[index])) + str("%02x" % (header[index + 1])), 16)
        size -= 2
        index += 2
        
    while X > 0xFFFF:
        X0 = X & 0xFFFF
        X1 = X >> 16
        X = X0 + X1

    new = ""
    for c in bin(X)[2:]:
        if c == "1":
            new += "0"
        elif c == "0":
            new += "1"    
    #print(new)
    #print(int(new, 2))
    
    #print(bin(X))
    #print(bin(~X))
    
    return int(new, 2)