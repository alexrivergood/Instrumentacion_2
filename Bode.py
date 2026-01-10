import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt(r"C:\Users\Marcos\Desktop\Master en Física y tecnologias Físicas\1º Cuatri\Instrumentación\Proyecto LMX\Medidas pasabanda\medidas_bode_fgraves8promreostato.txt", skiprows=1)

freq = data[:, 0]
mag = data[:, 1]
mag_err = data[:, 2]
phase = data[:, 3]
phase_err = data[:, 4]

data_extra = np.loadtxt(r"C:\Users\Marcos\Desktop\Master en Física y tecnologias Físicas\1º Cuatri\Instrumentación\Proyecto LMX\Medidas pasabanda\simulado 3,0 reostato.txt", skiprows=1)

freq_extra = data_extra[:, 0]
mag_extra = data_extra[:, 1]
#mag_err_extra = data_extra[:, 2]
phase_extra = data_extra[:, 2]
#phase_err_extra = data_extra[:, 4]

valor_minimo = min(phase)



phase_extra = [
    valor + 360 if valor <= valor_minimo else valor
    for valor in phase_extra
]



fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(8, 7), sharex=True)


ax1.errorbar(freq, mag, yerr=mag_err, fmt='-o', color='navy',
             markersize=4, linewidth=1.8, capsize=3, label='Datos experimentales')
ax1.errorbar(freq_extra, mag_extra, fmt='-', color='orange',
             markersize=4, linewidth=1.5, capsize=3, label='Tina-Ti')

ax1.set_xscale('log')
ax1.set_ylabel('Ganancia [dB]', fontsize=14)
ax1.set_title('Diagrama de Bode', fontsize=16, pad=20)
ax1.grid(True, which='major', linestyle='-', linewidth=0.6, alpha=0.8)
ax1.grid(True, which='minor', linestyle='--', linewidth=0.4, alpha=0.5)
ax1.legend(fontsize=11, loc='best')
ax1.tick_params(axis='both', which='major', labelsize=12, width=1.2)
ax1.tick_params(axis='both', which='minor', width=0.8)


ax2.errorbar(freq, phase, yerr=phase_err, fmt='-o', color='darkred',
             markersize=4, linewidth=1.8, capsize=3, label='Datos experimentales')
ax2.errorbar(freq_extra, phase_extra, fmt='-', color='darkorange',
             markersize=4, linewidth=1.5, capsize=3, label='Tina-Ti')

ax2.set_xscale('log')
ax2.set_xlabel('Frecuencia [Hz]', fontsize=14)
ax2.set_ylabel('Fase [°]', fontsize=14)
ax2.grid(True, which='major', linestyle='-', linewidth=0.6, alpha=0.8)
ax2.grid(True, which='minor', linestyle='--', linewidth=0.4, alpha=0.5)
ax2.legend(fontsize=11, loc='best')
ax2.tick_params(axis='both', which='major', labelsize=12, width=1.2)
ax2.tick_params(axis='both', which='minor', width=0.8)

ax1.set_xlim(50, 20000)
fig.subplots_adjust(left=0.05, right=0.95, top=0.93, bottom=0.12, hspace=0.25)


fig.subplots_adjust(
    left=0.08,   
    right=0.97,
    top=0.92,
    bottom=0.10,
    hspace=0.25
)
plt.show()
