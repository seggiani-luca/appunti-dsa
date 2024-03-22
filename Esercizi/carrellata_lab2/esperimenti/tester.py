import subprocess
size = int(input("Enter instance size: "))
instances = int(input("Enter amount of instances: "))
treshold = int(input("Enter optimization treshold: "))
verbose = input('Verbose? (y/n): ').lower().strip() == 'y'


timeTotal = 0

for i in range(instances):
    verbose_flag = "n"
    if(verbose):
        verbose_flag = "y"
    command = './hybrid_sort {} {} {}'.format(size, treshold, i, verbose_flag)
    process = subprocess.Popen(f'bash -c "time {command}"', stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    output, error = process.communicate()
    
    time = float(str(error)[12 : 17])
    print("Iteration " + str(i) + " elapsed " + str(time) + "ms")
    timeTotal += time
    if(verbose):
        print(output.decode('utf-8'))
        print(error.decode('utf-8'))

timeTotal /= instances
print("Average elapsed time is " + str(timeTotal) + "ms")
