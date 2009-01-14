hostname R21
!
interface Loopback0
 ip address 10.10.10.21 255.255.255.255
!
interface Serial0/0
 no shut
 bandwidth 512
 ip address 10.1.1.18 255.255.255.252
!
interface Serial0/1
 bandwidth 512
 no shut
 ip address 10.1.1.21 255.255.255.252
!
router ospf 9
 network 10.1.1.0 0.0.0.255 area 9
 network 10.10.10.0 0.0.0.255 area 9
