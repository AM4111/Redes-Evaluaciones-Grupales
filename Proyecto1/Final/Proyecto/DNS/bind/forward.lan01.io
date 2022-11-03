$TTL    1D
@       IN      SOA     lan01.io. root.lan01.io. (
        1               ; Serial
        12h             ; Refresh
        15m             ; Retry
        3w              ; Expire
        2h  )           ; Negative Cache TTL

;       Registros NS

        IN      NS      lan01.io.
dhcp1   IN      A       10.0.0.4