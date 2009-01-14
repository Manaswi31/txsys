hostname R10
!
interface Serial0/0
 no shut
 bandwidth 512
 ip address 10.1.1.6 255.255.255.252
!
interface Serial0/1
 no shut
 bandwidth 512
 ip address 10.1.1.13 255.255.255.252
!
router ospf 9
 network 10.1.1.0 0.0.0.255 area 9
 network 10.10.10.0 0.0.0.255 area 9
end
