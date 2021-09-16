# Dimmer RMS

**_Se recomienda abrir las imagenes en pestañas nuevas para su mejor visualización._**

## Roadmap

- [ ] Acondicionar señal.
- [ ] Manejar interrupción.
- [ ] Implementar frecuencimetro.
- [ ] Implementar método para obtener tiempo de trigger para objetivo duty.\
       Podría implementarse por busqueda en una tabla o por método numérico.
- [ ] Implementar comunicación I2C con maestro.

## Signal conditioning

Partiendo de una señal alterna dada por una senoidal fundamental y otra senoidal de mayor frecuencia y menor amplitud.


<!-- $$
vsin(t) = 150v \cdot \sin(2\pi \cdot 50Hz  \cdot t)
vnoise(t) = 2v \cdot \sin(2\pi \cdot 10kHz \cdot t)
v(t) = vsin(t) + vnoise(t)
$$ --> 
<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=vsin(t)%20%3D%20150v%20%5Ccdot%20%5Csin(2%5Cpi%20%5Ccdot%2050Hz%20%20%5Ccdot%20t)"></div>
<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=vnoise(t)%20%3D%202v%20%5Ccdot%20%5Csin(2%5Cpi%20%5Ccdot%2010kHz%20%5Ccdot%20t)"></div> 
<div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=v(t)%20%3D%20vsin(t)%20%2B%20vnoise(t)"></div> 


Se comparan dos diseños:

- ZCD clásico. Rectificador de onda completa con salida optoacoplada.
- ZCD adaptado. ZCD clásico con amplificador intermedio.

<p align="center">
<img src="./model/ZeroCross/Zero%20Cross.BMP" width="60%"/>
</p>

En el diseño adaptado, se han implementado algunas modificaciones.
- Filtro pasa bajos. Compuesto por R1/C1 y R2/C1 según el semiciclo.
  <!-- $$
  LPF = \frac{1}{(2\pi \cdot 220k\Omega \cdot 1nF)} \approx 720Hz
  $$ --> 
  <div align="center"><img style="background: white;" src="https://render.githubusercontent.com/render/math?math=LPF%20%3D%20%5Cfrac%7B1%7D%7B(2%5Cpi%20%5Ccdot%20220k%5COmega%20%5Ccdot%201nF)%7D%20%5Capprox%20720Hz"></div>
- Fuente CC primitiva. Compuesta por D1, C2 y R3. El capacitor de esta fuente debe almacenar la suficiente energía para alimentar al optoacoplador durante la mayor parte del semiperíodo.\
  Las resistencias R1 y R2 deberán tener el valor adecuado para garantizar la recarga de C2 en el tiempo que dure la detección de cruce.
- Amplificador clase E. Permanente en estado alto salvo en los cruces por cruce de cero. En dicho cruce al abrirse Q1, dado el pull up, la salida optoacoplada tiene salida en alto.

Las oscilografías siguientes corresponden al detecctor clásico y al modificado respectivamente.

<p align="center">
<img src="model/ZeroCross/1-ZCD Normal.png" alt="1-ZCD Normal.png" width="45%" />
<img src="model/ZeroCross/2-ZCD Boost.png" alt="2-ZCD Boost" width="45%" />

<img src="model/ZeroCross/3-ZCD Normal - Detail.png" alt="3-ZCD Normal - Detail" width="45%" />
<img src="model/ZeroCross/4-ZCD Boost - Detail.png" alt="4-ZCD Boost - Detail" width="45%" />
</p>

- En el detector clásico, el umbral de detección se presenta 180us antes del cruce y perdura hasta casi 320us después del mismo.
- En el detector modificado, el umbral de detección se presenta 53us después del cruce.
- Siendo lo importante el flanco ascendente de detección, se mejora el tiempo de detección en un 70.88%