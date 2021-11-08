import math
def number_fdma_channels (b_hz, g_hz, u_hz):
    """Overall system bandwidth = b, required guard band bandwidth = g,
       bandwidth required for sub channel = u. This function finds the maximum
       number of users than can be accomodated on the system"""
    available_bandwidth = b_hz - g_hz #Take off one guard band since we need N+1 guard bands
    sub_channel_req = g_hz + u_hz
    num_users = math.floor(available_bandwidth / sub_channel_req)
    return num_users
    