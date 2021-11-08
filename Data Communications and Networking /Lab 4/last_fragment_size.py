import math
def last_fragment_size (messageSize_bytes, overheadPerPacket_bytes, maximumNPacketSize_bytes):
    s = messageSize_bytes
    o = overheadPerPacket_bytes
    m = maximumNPacketSize_bytes
    max_payload_size = m - o
    num_fragments = math.ceil(s / max_payload_size)
    size_last_frag = o + (s % max_payload_size)
    return size_last_frag
#return o + (s % (m - o))