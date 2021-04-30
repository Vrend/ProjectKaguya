# CTF GUIDE



---


**<span style="text-decoration:underline;">Spoilers Below!</span>**



---

<br/>
<br/>
<br/>

1. Telnet into the flag server with username ‘anonymous’
2. Port scan both the plane system and the router
    1. Connect with netcat on port 5000 on the plane system to see locked frontend
3. Find website accessible from router, and read page sources
4. Exploit web server using sql injection to get a user-level interactive shell
    1. [https://resources.infosecinstitute.com/topic/anatomy-of-an-attack-gaining-reverse-shell-from-sql-injection/](https://resources.infosecinstitute.com/topic/anatomy-of-an-attack-gaining-reverse-shell-from-sql-injection/)
5. Generate a meterpreter payload on kali, and run the generic multi handler
6. Put the meterpreter payload in /var/www/html and wget the payload on the webserver
7. Execute the meterpreter and pivot using autoroute
8. nmap scan internal LAN using proxychains or metasploit scan
9. Can be done in any order:
    1. Exploit IRC server to read logs with information on “lock system” and the internal interface port for plane system (app is ‘locked’ to input changes, variable is still there)
        1. [https://www.rapid7.com/db/modules/exploit/unix/irc/unreal_ircd_3281_backdoor/](https://www.rapid7.com/db/modules/exploit/unix/irc/unreal_ircd_3281_backdoor/)
    2. Exploit Host1 using postgresql cmd_exec to find pw_reminder.txt in the home folder of paul, which can then be used to ssh in. There’s a ‘notes’ folder in home directory, filled with encrypted file and txt file explaining his ‘genius’ security, but not full information
        1. [https://null-byte.wonderhowto.com/how-to/gather-information-postgresql-databases-with-metasploit-0218317/](https://null-byte.wonderhowto.com/how-to/gather-information-postgresql-databases-with-metasploit-0218317/)
    3. Exploit Host2 using libssh auth bypass for IRC log between Host2 and Host3 which gives username and password for FTP server
        1. [https://www.rapid7.com/db/modules/auxiliary/scanner/ssh/libssh_auth_bypass/](https://www.rapid7.com/db/modules/auxiliary/scanner/ssh/libssh_auth_bypass/)
        2. Connect to FTP server and look at plane system source code
    4. Exploit Host3 using samba for IRC log between Host1 and Host3 talking about his encryption algorithm
        1. [https://medium.com/@lucideus/sambacry-rce-exploit-lucideus-research-3a3e5bd9e17c](https://medium.com/@lucideus/sambacry-rce-exploit-lucideus-research-3a3e5bd9e17c)
        2. Exfiltrate notes and decrypt/decode for ssh account for plane system
10. SSH into plane system with found login, and find server running on UDP port 5001 on loopback
11. Use binary exploitation to set ‘locked’ to 0
    1. [https://www.tallan.com/blog/2019/04/04/exploring-buffer-overflows-in-c-part-two-the-exploit/](https://www.tallan.com/blog/2019/04/04/exploring-buffer-overflows-in-c-part-two-the-exploit/)
12. Change plane conditions to crash plane
13. Read /var/log/plane.log for flag
14. Submit flag to flag system for victory
