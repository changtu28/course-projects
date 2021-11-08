def connection_setup_delay (cableLength_km, speedOfLight_kms, dataRate_bps, messageLength_b, processingTimes_s):
    """Calculates how long the connection setup phase (time between point A
    starting the process and A being able to commence data transmission)"""
    prop_delay = cableLength_km / speedOfLight_kms  #Propogation Delay
    trans_delay = messageLength_b / dataRate_bps    #Transmission Delay
    setup_delay = prop_delay + trans_delay + processingTimes_s #Total time in seconds it takes to transmit and process the request/response
    return setup_delay * 4 #setup_delay for A->B, B->C (request), C->B, B->A (response)

def message_delay (connSetupTime_s, cableLength_km, speedOfLight_kms, messageLength_b, dataRate_bps):
    """Calculates how long it takes to setup a connection and transmit a message
    """
    trans_delay = messageLength_b / dataRate_bps  #Transmission Delay
    #print(trans_delay)
    prop_delay = cableLength_km / speedOfLight_kms  #Propogation Delay
    #print(prop_delay)
    return connSetupTime_s + trans_delay + (2 * prop_delay)

import math
def total_number_bits (maxUserDataBitsPerPacket_b, overheadBitsPerPacket_b, messageLength_b):
    """The total number of bits (both userdata and overhead) that need to be
    transmitted to transmit all M user data bits in packets"""
    S = maxUserDataBitsPerPacket_b
    O = overheadBitsPerPacket_b
    M = messageLength_b
    numPackets = math.ceil(M / S)
    return (O * numPackets) + messageLength_b


def packet_transfer_time (linkLength_km, speedOfLight_kms, processingDelay_s, dataRate_bps, maxUserDataBitsPerPacket_b, overheadBitsPerPacket_b):
    """The time it takes to start a transmission of a packet from A, through B
    and to C including processing time"""
    L = linkLength_km
    C = speedOfLight_kms
    P = processingDelay_s
    R = dataRate_bps
    S = maxUserDataBitsPerPacket_b
    O = overheadBitsPerPacket_b
    prop_delay = L / C                      #Propogation Delay
    trans_delay = (S + O) / R               #Transmission Delay
    trans_total = prop_delay + trans_delay  #Transfer total time (not incl processing)
    total_time = trans_total + P            #Transfer time + processing time (eg. A -> B)
    return total_time * 2 #A->B, B->C


def total_transfer_time (linkLength_km, speedOfLight_kms, processingDelay_s, dataRate_bps, maxUserDataBitsPerPacket_b, overheadBitsPerPacket_b, messageLength_b):
    L, C, P, R, S, O, M = linkLength_km, speedOfLight_kms, processingDelay_s, dataRate_bps, maxUserDataBitsPerPacket_b, overheadBitsPerPacket_b, messageLength_b
    numPackets = (M/S)
    prop_delay = L / C                      #Propogation Delay
    trans_delay = (S + O) / R               #Transmission Delay for one packet
    multi_trans_delay = ((S + O) * (numPackets - 1)) / R
    total_time = (2 * prop_delay) + (2 * P) + (2 * trans_delay) + multi_trans_delay 
    """propogation delays & processing delays for first packet and last packet, 
    transmission delay for first packet, multi trans for rest of packets"""
    return total_time