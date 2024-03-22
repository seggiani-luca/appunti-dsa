import subprocess

def test_instance(size, instances, treshold):
    timeTotal = 0
    for i in range(instances):
        verbose_flag = "n"
        command = './hybrid_sort {} {} {}'.format(size, treshold, i, verbose_flag)
        process = subprocess.Popen(f'bash -c "time {command}"', stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
        output, error = process.communicate()
        time = str(error)[12 : 17]
        timeTotal += float(time)
    timeTotal /= instances
    print(str(size) + "," + str(treshold) + "," + str(timeTotal)) 

instances = int(input("Enter instance number: "))
optimization_range = int(input("Enter optimization value test range: "))

print("SIZE,TRESHOLD,TIME")
#for i in range(1, 10):
size = 1000000
for j in range(optimization_range):
    treshold = j
    test_instance(size, instances, treshold)
