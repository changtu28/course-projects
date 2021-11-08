import math
def number_fragments (messageSize_bytes, overheadPerPacket_bytes, maximumNPacketSize_bytes):
    s = messageSize_bytes
    o = overheadPerPacket_bytes
    m = maximumNPacketSize_bytes
    max_payload_size = m - o
    num_fragments = math.ceil(s / max_payload_size)
    #General expression = return math.ceil(s / (m - o))
    return num_fragments