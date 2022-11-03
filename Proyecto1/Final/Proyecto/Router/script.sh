#!/bin/bash
#TCP
#iptables -A INPUT -p tcp -m multiport --dports 53,80,443,3128,8443 -j ACCEPT

echo 1 > /proc/sys/net/ipv4/ip_forward
iptables-legacy  -A INPUT -p tcp --sport 53 -j ACCEPT
iptables-legacy  -A INPUT -p tcp --sport 80 -j ACCEPT
iptables-legacy  -A INPUT -p tcp --sport 443 -j ACCEPT
iptables-legacy  -A INPUT -p tcp --sport 3128 -j ACCEPT
iptables-legacy  -A INPUT -p tcp --sport 8443 -j ACCEPT
#UDP
#iptables -A INPUT -p upd --dports 53 -j ACCEPT
iptables-legacy -A INPUT -p udp --dport 53 -j ACCEPT
tail -f /dev/null