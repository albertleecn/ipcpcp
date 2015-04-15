This project explains the producer and comsumer problem with multi-threads.
function:
    multi-producers, multi-comsumers, fixed-buffer, max produce/comsume items
tech:
pthread_mutex
semaphore

example:
Begin:Producer and Consumer Problem
0   1   2
*   *   *
Creating the 1th Comsumer Thread(2625536)
Creating the 2th Comsumer Thread(3162112)
Creating the 3th Comsumer Thread(3698688)
Creating the 4th Comsumer Thread(4235264)
Creating the 5th Comsumer Thread(4771840)
Creating the 11th Producer Thread(5308416)
Creating the 12th Producer Thread(5844992)
Creating the 13th Producer Thread(6381568)
Creating the 14th Producer Thread(6918144)
hi, I am the 4th comsumer thread(4235264)
hi, I am the 3th comsumer thread(3698688)
hi, I am the 5th comsumer thread(4771840)
hi, I am the 12th producer thread(5844992)
hi, I am the 11th producer thread(5308416)
hi, I am the 13th producer thread(6381568)
hi, I am the 14th producer thread(6918144)
the 12th producer thread enters critical region
0   1   2
*   *   *
hi, I am the 2th comsumer thread(3162112)
hi, I am the 1th comsumer thread(2625536)
thread(12) produces:2:id=1,producerId=12,time=Wed Apr 15 11:32:05 2015
0   1   2
*   *   1
the 12th producer thread leaves critical region!
the 11th producer thread enters critical region
0   1   2
*   *   1
thread(11) produces:0:id=2,producerId=11,time=Wed Apr 15 11:32:06 2015
0   1   2
2   *   1
the 11th producer thread leaves critical region!
the 4th comsumer thread enters critical region
0   1   2
2   *   1
2:id=1,producerId=12,time=Wed Apr 15 11:32:05 2015
thread(4) comsumes:id=1,producerId=12,time=Wed Apr 15 11:32:05 2015
0   1   2
2   *   *
the 4th comsumer thread leaves critical region!
the 13th producer thread enters critical region
0   1   2
2   *   *
thread(13) produces:1:id=3,producerId=13,time=Wed Apr 15 11:32:10 2015
0   1   2
2   3   *
the 13th producer thread leaves critical region!
the 3th comsumer thread enters critical region
0   1   2
2   3   *
0:id=2,producerId=11,time=Wed Apr 15 11:32:06 2015
thread(3) comsumes:id=2,producerId=11,time=Wed Apr 15 11:32:06 2015
0   1   2
*   3   *
the 3th comsumer thread leaves critical region!
the 14th producer thread enters critical region
0   1   2
*   3   *
thread(14) produces:0:id=4,producerId=14,time=Wed Apr 15 11:32:12 2015
0   1   2
4   3   *
the 14th producer thread leaves critical region!
the 5th comsumer thread enters critical region
0   1   2
4   3   *
0:id=4,producerId=14,time=Wed Apr 15 11:32:12 2015
thread(5) comsumes:id=4,producerId=14,time=Wed Apr 15 11:32:12 2015
0   1   2
*   3   *
the 5th comsumer thread leaves critical region!
the 12th producer thread enters critical region
0   1   2
*   3   *
thread(12) produces:2:id=5,producerId=12,time=Wed Apr 15 11:32:15 2015
0   1   2
*   3   5
the 12th producer thread leaves critical region!
the 2th comsumer thread enters critical region
0   1   2
*   3   5
2:id=5,producerId=12,time=Wed Apr 15 11:32:15 2015
thread(2) comsumes:id=5,producerId=12,time=Wed Apr 15 11:32:15 2015
0   1   2
*   3   *
the 2th comsumer thread leaves critical region!
the 11th producer thread enters critical region
0   1   2
*   3   *
thread(11) produces:0:id=6,producerId=11,time=Wed Apr 15 11:32:17 2015
0   1   2
6   3   *
the 11th producer thread leaves critical region!
the 1th comsumer thread enters critical region
0   1   2
6   3   *
0:id=6,producerId=11,time=Wed Apr 15 11:32:17 2015
thread(1) comsumes:id=6,producerId=11,time=Wed Apr 15 11:32:17 2015
0   1   2
*   3   *
the 1th comsumer thread leaves critical region!
the 13th producer thread enters critical region
0   1   2
*   3   *
thread(13) produces:2:id=7,producerId=13,time=Wed Apr 15 11:32:20 2015
0   1   2
*   3   7
the 13th producer thread leaves critical region!
the 4th comsumer thread enters critical region
0   1   2
*   3   7
2:id=7,producerId=13,time=Wed Apr 15 11:32:20 2015
thread(4) comsumes:id=7,producerId=13,time=Wed Apr 15 11:32:20 2015
0   1   2
*   3   *
the 4th comsumer thread leaves critical region!
the 14th producer thread enters critical region
0   1   2
*   3   *
thread(14) produces:2:id=8,producerId=14,time=Wed Apr 15 11:32:23 2015
0   1   2
*   3   8
the 14th producer thread leaves critical region!
the 13th producer thread exit.
the 3th comsumer thread enters critical region
0   1   2
*   3   8
1:id=3,producerId=13,time=Wed Apr 15 11:32:10 2015
thread(3) comsumes:id=3,producerId=13,time=Wed Apr 15 11:32:10 2015
0   1   2
*   *   8
the 3th comsumer thread leaves critical region!
the 4th comsumer thread exit.
the 12th producer thread enters critical region
0   1   2
*   *   8
thread(12) produces:1:id=9,producerId=12,time=Wed Apr 15 11:32:27 2015
0   1   2
*   9   8
the 12th producer thread leaves critical region!
the 14th producer thread exit.
the 5th comsumer thread enters critical region
0   1   2
*   9   8
2:id=8,producerId=14,time=Wed Apr 15 11:32:23 2015
thread(5) comsumes:id=8,producerId=14,time=Wed Apr 15 11:32:23 2015
0   1   2
*   9   *
the 5th comsumer thread leaves critical region!
the 3th comsumer thread exit.
the 11th producer thread enters critical region
0   1   2
*   9   *
thread(11) produces:0:id=10,producerId=11,time=Wed Apr 15 11:32:30 2015
0   1   2
10   9   *
the 11th producer thread leaves critical region!
the 12th producer thread exit.
the 2th comsumer thread enters critical region
0   1   2
10   9   *
0:id=10,producerId=11,time=Wed Apr 15 11:32:30 2015
thread(2) comsumes:id=10,producerId=11,time=Wed Apr 15 11:32:30 2015
0   1   2
*   9   *
the 2th comsumer thread leaves critical region!
the 5th comsumer thread exit.
the 11th producer thread exit.
the 1th comsumer thread enters critical region
0   1   2
*   9   *
1:id=9,producerId=12,time=Wed Apr 15 11:32:27 2015
thread(1) comsumes:id=9,producerId=12,time=Wed Apr 15 11:32:27 2015
0   1   2
*   *   *
the 1th comsumer thread leaves critical region!
the 2th comsumer thread exit.
the 1th comsumer thread exit.
End:Producer and Consumer Problem
