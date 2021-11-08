def transmission_delay (packetLength_bytes, rate_mbps):
    """Calculates the transmissions delay given the size of the transmission
    and the speed of the transmission"""
    packetLength_bits = packetLength_bytes * 8
    packetLength_megaBits = packetLength_bits / 1000 / 1000
    return packetLength_megaBits / rate_mbps

