import math
def number_tdma_users (s_s, g_s, u_s):
    """Superframe length = s, guard time = g, length of user slot = u (all in 
       seconds). This function finds the maximum number of users that the TDMA
       system can support."""
    #available_time = s_s #Take off one guard band since we need N+1 guard bands
    sub_channel_req = g_s + u_s
    num_users = math.floor(s_s / sub_channel_req)
    return num_users