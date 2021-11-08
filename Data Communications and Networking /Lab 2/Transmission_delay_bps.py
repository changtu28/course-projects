def transmission_delay (packetLength_bytes, rate_bps):
    """Calculates the transmissions delay given the size of the transmission
    and the speed of the transmission"""
    packetLength_bits = packetLength_bytes * 8
    return packetLength_bits / rate_bps

