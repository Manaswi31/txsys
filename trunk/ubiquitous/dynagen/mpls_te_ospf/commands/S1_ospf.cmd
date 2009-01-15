hostname S1
!
!
interface Loopback0
 ip address 10.10.10.100 255.255.255.255
!
interface Serial0/0
 no shut
 bandwidth 512
 ip address 10.1.1.1 255.255.255.252
 serial restart-delay 0
!
!
router ospf 9
 log-adjacency-changes
 network 10.1.1.0 0.0.0.255 area 9
 network 10.10.10.0 0.0.0.255 area 9
