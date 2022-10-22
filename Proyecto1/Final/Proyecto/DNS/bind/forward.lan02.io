$TTL    1D
@       IN      SOA     lan02.io. root.lan02.io. (
        1               ; Serial
        12h             ; Refresh
        15m             ; Retry
        3w              ; Expire
        2h  )           ; Negative Cache TTL

;       Registros NS

        IN      NS      lan02.io.
dhcp2   IN      A       10.0.1.5