$TTL    1D
@       IN      SOA     google.com. www.google.com. (
        1               ; Serial
        12h             ; Refresh
        15m             ; Retry
        3w              ; Expire
        2h  )           ; Negative Cache TTL

;       Registros NS

        IN      NS      google.com.
www     IN      A       8.8.8.8
www     IN      AA      8.8.8.9