# Lock-FreeSPSCRingBuffer
A Ring Buffer Alorgirthm optimized without the use of &lt;mutex>
When programming in the Digital Signal Processing world, a big issue is time constraints. Because audio is countinous, waiting or "locking" a action from occur can cause major problems for the listner and scientist. This can be forms of pops or the apparent absent of audio. 

To address this concern, many DSP engineers stictly avoid the <mutex> header and the <conditionalvarible> respectfully. So how would you implement a multi-threaded ring buffer without using these header? I used the <atomic> header looked deeper at the core functionalites of memory exchange and how it is accessed in the complier. By manipulating the memory under the hood, I was able to make a pseudo replica of the <mutex> header without using. This is because memory is the building blocks of computers and using memory_order keywords, I was able to let the program flow naturally and not stop. 
