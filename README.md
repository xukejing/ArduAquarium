# ArduAquarium

a fish tank controlled by Arduino  
这是个arduino控制的鱼缸。  
  
蓝牙串口交互。通讯协议见serial，通讯协议的间隔符号是英文逗号。  
温度控制模拟了一天里的温度变化，见control里的realtemp函数和tempur control函数。  
水泵可以手动开关或自动定时控制。自动时，一天最多256次开关控制。只控制上滤槽水泵。底部过滤桶的水泵不关。
臭氧自动定时，为了安全就没有做时间设置接口。固定8点和17点自动开始消毒，如果臭氧发生器流量大，需要改代码缩短时间。临时手动开启消毒20秒可以这样，“so20,”  
  
控制参数会存入epprom，掉电后再启动会读取epprom，见eeprom put get。  
