import numpy as np
from matplotlib import pyplot as plt

def spring_motion(spring_init, coef1, coef2, t, d):

    toDisplay = bool(input("Would you like to view data? (0/1): "))

    runtime = 0.0
    spring_final = {}

    x_set, v_set, a_set, t_set = [], [], [], []

    if toDisplay:
        print("t (time)\t x (position)\t v (velocity)\t a (acceleration)")

    while runtime < t:

        x_set.append(spring_init['x'])
        v_set.append(spring_init['v'])
        a_set.append(spring_init['a'])
        t_set.append(runtime)

        if toDisplay:
            print("%.4f\t %.4f\t %.4f\t %.4f" % (runtime,spring_init['x'],spring_init['v'],spring_init['a']))

        spring_final['a'] = coef1*spring_init['x'] + coef2*spring_init['v']
        spring_final['v'] = spring_init['v'] + spring_final['a']*d
        spring_final['x'] = spring_init['x'] + spring_final['v']*d

        spring_init = spring_final
        runtime = runtime + d

    x_set = np.array(x_set)
    v_set = np.array(v_set)
    a_set = np.array(a_set)
    t_set = np.array(t_set)

    f, (ax1, ax2, ax3) = plt.subplots(nrows = 3, sharex = True)

    ax1.plot(t_set, x_set, color = 'red')
    ax1.set_title("Position vs Time")

    ax2.plot(t_set, v_set, color = 'blue')
    ax2.set_title("Velocity vs Time")

    ax3.plot(t_set, a_set, color = 'orange')
    ax3.set_title("Acceleration vs Time")

    plt.show()


def spring_motion_input():

    print("---> Spring Motion <---")

    print("Notes:")
    print("Recommended digression value: 0.001")
    print("For high frequency, k / m ratio must be high (~20)")
    print("For observing damped oscillations, either d must be close to 1, or time of simulation must be high")
    print("For model input, type: 5, 0, 1, 100, 1, 10, 0.01, 1")

    print("-----------------------")

    spring_init = {}
    spring_init['x'] = float(input("Enter initial position (with sign): "))
    spring_init['v'] = float(input("Enter initial velocity (with sign): "))
     
    m = float(input("Enter mass of the spring: "))
    k = float(input("Enter spring constant: "))
    b = float(input("Enter damping constant of the medium: "))

    t = float(input("Enter time of simulation: "))
    d = float(input("Enter digression tolerable: "))

    coef1 = - k / m
    coef2 = - b / m

    spring_init['a'] = coef1*spring_init['x'] + coef2*spring_init['v']

    spring_motion(spring_init, coef1, coef2, t, d)


if __name__ == '__main__':
    spring_motion_input()