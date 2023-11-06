PS1=">>  "
PS2="sawrm$ "

def display(str):
    global PS1
    print(PS1+str)

# Initializing Swarm
def Create_Swarm(script):

    display("creating swarm")
    return None

# Creating a task
def Create_task(script):
    display("Task is created")
    return None
# Creatins script
def Create_script():
    display("Script is created")
    return None
# Exit from console
def quit(script):
    display("exiting...")
    exit(0)

# symulating one step
def Step(script):
    display("Step was done")

def Run_task(script):
    display("Running task")

def Run_script(script):
    display("Running script")


def show_menu(menu):
    for i,(menu_str, _) in enumerate(menu):
        print(f'{i+1}. {menu_str}')

    while True:
        try:
            num_str = input(PS2)
            num = int(num_str)
            return menu[num-1][1]
        except (ValueError, IndexError):
            print(f'Please enter a number from 1 to {len(menu)}')
            pass
    

if __name__ == "__main__":
    menu =[ 
        (" Create Swarm", Create_Swarm),
        (" Create task", Create_task),
        (" Create Step", Step),
        (" Run task", Run_task),
        (" Run script", Run_script),
        (" quit", quit)
        ]
    script = Create_script()
    while(1):
        func = show_menu(menu)
        func(script)
