def per_from_ber (bitErrorProb, packetLen_b):
    return 1 - ((1 - bitErrorProb)**packetLen_b)

def avg_trials_from_ber (bit_error_probability, packetLength_b):
    prob_1_bad_bit = 1 - ((1 - bit_error_probability)**packetLength_b)
    return (1/(1-prob_1_bad_bit))