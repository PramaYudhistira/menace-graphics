<h3> How to Run</h3>
* Use cmake, not the shell script
TODO: work on implementing shell script

<h4>Linux</h4>


* If system has hybrid graphics setup, (example: Ryzen 9 7000 series with integrated graphics and a separate 4060):
    * make sure the target gpu is accessible. With nvidia run `nvidia-smi`
    * TODO: cannot figure out this issue, still getting errors with zink driver not finding a gpu to render ```bash MESA: error: ZINK: failed to choose pdev```
        * The executable is running fine so I will ignore the message for now.


* run `mkdir build && cd build`, then run `cmake ..`
    * run `make`, this should compile and give the binary for you to run

<h4>TODO: Windows</h4>

