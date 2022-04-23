# bpc-ic1-proj

Project from subject BPC-IC1

## How to setup

1. `git clone https://github.com/Charashenko/bpc-ic1-proj.git`
1. `cd` into new directory
1. Run `make`
1. Download `rockyou` dictionary and place it in the `resources` folder
1. Download `john the ripper` utility
1. Use `python exploits.py [number of exploit] [user]` where number of exploit can be: 1-3
   - if **no number** is specified, 1. exploit will be executed
   - if number **3** is specified, you need to input **[user]** whose passwd will be cracked, otherwise **root** will

## Showcase

### First exploit - Buffer overflow

---

Code where exploit occurs:

![](/images/bo1.png "Code where exploit occurs")

Result is "admin mode" which is not otherwise accessible:

![](/images/bo2.png "Result of buffer overflow")

---

### Second exploit - Python library hijacking

---

Attacker has write permissions to **exploitable.py** module which is used by **syntaxchecker.py** script. With that, original **exploitable.py** can be used for root access if overwritten.

Overwitten function:

![](/images/plh1.png "Overwritten function")

Result of exploit:

![](/images/plh2.png "Result of python library hijacking exploit")

---

### Third exploit - Password cracking

---

Second exploit resulted in root shell. With that we can extract passwords and with utility **john the ripper** and wordlist **rockyou** we can try to crack it.

Used the third exploit:

![](/images/pc1.png "Example usage")

Result of the exploit:

![](/images/pc2.png "Result of password cracking")
