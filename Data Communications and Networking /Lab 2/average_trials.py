def average_trials (P):
    """The average number of packet transmission trials the transmitter has to
    make when the packet loss probability is P in (0, 1)"""
    return (1/(1-P))