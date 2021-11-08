def total_time (cableLength_KM, packetLength_b):
    dataRate_gb = 10 #Gbps
    dataRate_b = dataRate_gb * 1000 * 1000 * 1000
    cableSpeed = 200000 #km/s
    propDelay = cableLength_KM / cableSpeed
    transDelay = packetLength_b / dataRate_b
    totalTime_s = propDelay + transDelay
    totalTime_ms = totalTime_s * 1000
    return totalTime_ms