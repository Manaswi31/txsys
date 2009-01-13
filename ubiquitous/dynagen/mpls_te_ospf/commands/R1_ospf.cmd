hostname R1
!
ip cef

interface Loopback0
 no shut
 ip address 10.10.10.1 255.255.255.255
!
interface Serial0/0
 on shut
 bandwidth 512
 ip address 10.1.1.2 255.255.255.252
!
interface Serial0/1
 bandwidth 512
 ip address 10.1.1.5 255.255.255.252
 serial restart-delay 0
!
interface Serial0/2
 ip address 10.1.1.9 255.255.255.252
!
interface Serial0/3
 no ip address
 shutdown
 serial restart-delay 0
!
router ospf 9
 network 10.1.1.0 0.0.0.255 area 9
 network 10.10.10.0 0.0.0.255 area 9
