Initialize an array of N mutexes for forks
Initialize an array of N philosopher threads

Define function philosopher_behavior(philosopher_id):
    while True:
        print "Philosopher [philosopher_id] is thinking"
        sleep(random time)

        if philosopher_id is even:
            lock the left fork (mutex[philosopher_id])
            print "Philosopher [philosopher_id] has taken the left fork"
            lock the right fork (mutex[(philosopher_id + 1) % N])
            print "Philosopher [philosopher_id] has taken the right fork"
        else:
            lock the right fork (mutex[(philosopher_id + 1) % N])
            print "Philosopher [philosopher_id] has taken the right fork"
            lock the left fork (mutex[philosopher_id])
            print "Philosopher [philosopher_id] has taken the left fork"

        print "Philosopher [philosopher_id] is eating"
        sleep(random time)

        unlock the left fork (mutex[philosopher_id])
        print "Philosopher [philosopher_id] has put down the left fork"
        unlock the right fork (mutex[(philosopher_id + 1) % N])
        print "Philosopher [philosopher_id] has put down the right fork"

        print "Philosopher [philosopher_id] is sleeping"
        sleep(random time)

for i from 0 to N-1:
    initialize mutex[i]

for i from 0 to N-1:
    create a thread for philosopher_behavior(i)

for i from 0 to N-1:
    join thread[i]

for i from 0 to N-1:
    destroy mutex[i]
