def p_persistent_csma_collision_probability (p):
    """p for one station to transmit first time
       p^2 for both stations to transmit first time
       (1-p) * p for one station to transmit second time
       (1-p)^2 * p^2 for both stations to transmit second time
       (1-p)^4 * p^2 for both stations to transmit third time
       find general expression
       plug into / do something with geometric series formula"""
    