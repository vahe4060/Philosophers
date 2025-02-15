# Dining Philosophers

This project simulates the classic "Dining Philosophers" problem using multithreading in C. The simulation involves philosophers who alternately think, eat, and sleep, while sharing forks.


## How to run
	git clone https://github.com/vahe4060/Philosophers.git; cd Philosophers
    make
    ./philosophers 
    # Usage:
    #         ./philosophers [NUM_PHILOS] [TIME_TO_DIE] [TIME_TO_EAT][TIME_TO_SLEEP] [[NUM_MEALS]]
    # NUM_PHILOS      - number of philosophers
    # TIME_TO_DIE     - maximum time each philosopher can spend hungry/thinking (ms)
    # TIME_TO_EAT     - time each philosopher spends eating (ms)
    # TIME_TO_SLEEP   - time each philosopher spends sleeping (ms)
    # [NUM_MEALS]     - optional, number of meals for each philosopher.

```html
## Example
    vbox@demo:~/philosophers$ ./philosophers 3 100 40 20 3
    Time: 0ms
    Philo 0: to eat: 3, status: eating   
    Philo 1: to eat: 3, status: thinking 
    Philo 2: to eat: 3, status: <span style="color: yellow;">thinking</span> 
    Time: 43ms
    Philo 0: to eat: 2, status: sleeping 
    Philo 1: to eat: 3, status: thinking 
    Philo 2: to eat: 3, status: eating   
    Time: 68ms
    Philo 0: to eat: 2, status: thinking 
    Philo 1: to eat: 3, status: thinking 
    Philo 2: to eat: 3, status: eating   
    Time: 88ms
    Philo 0: to eat: 2, status: thinking 
    Philo 1: to eat: 3, status: thinking 
    Philo 2: to eat: 2, status: sleeping 
    Time: 113ms
    Philo 0: to eat: 2, status: thinking 
    Philo 1: to eat: 3, status: eating   
    Philo 2: to eat: 2, status: thinking 
    Time: 148ms
    Philo 0: to eat: 2, status: dead
    Philo 1: to eat: 2, status: sleeping 
    Philo 2: to eat: 2, status: thinking 

```
