import serial
import datetime
import numpy as np
arduino = serial.Serial('COM3', 2000000, timeout=.1)

global Final_Data
Final_Data = []

global z
z = True
counter = 0
while z:
    counter = counter+1
    while arduino.readline()[:-2]:
        arduino.flush()
    print("Number:"+str(counter))
    input("Press Enter to continue...")
    current_time = datetime.datetime.now()
    global x
    x = False
    while x ==False:
        data = arduino.readline()[:-2]
        if data:

            x=True
            data = []
    final_time = datetime.datetime.now()
    
    diff = (final_time-current_time)
    diff = float(diff.total_seconds())
    print(diff)
    aws = input("Done?")
    if aws == "Y":
        z = False
        arduino.close()
        Final_Data.append(diff)
    elif aws == "P":
        pass
        print("Point Passed")
        counter = counter-1
    else:
        Final_Data.append(diff)
# In[]
        
Final_Data = np.array(Final_Data)
np.savetxt("Data.txt",Final_Data)
np.save("Data",Final_Data)