# LoRa-Shrimp-Monitoring-Control
Abstract: The shrimp farming industry in Ecuador, renowned for its shrimp breeding and exportation, faces challenges due to diseases related to variations in abiotic factors during the maturation stage. This is partly attributed to the traditional methods employed in shrimp farms. Consequently, a prototype has been developed for monitoring and controlling abiotic factors using IoT technology. The proposed system consists of three nodes communicating through the LoRa interface. For control purposes, a fuzzy logic system has been implemented that evaluates temperature and dissolved oxygen abiotic factors to determine the state of the aerator, updating the information in the ThingSpeak application. A detailed analysis of equipment energy consumption and the maximum communication range for message transmission and reception was conducted. Subsequently, the monitoring and control system underwent comprehensive testing, including communication with the visualization platform. The results demonstrated significant improvements in system performance. By modifying parameters in the microcontroller, a 2.55-fold increase in battery durability was achieved. The implemented fuzzy logic system enabled effective on/off control of the aerators, showing a corrective trend in response to variations in the analyzed abiotic parameters. The robustness of the LoRa communication interface was evident in urban environments, achieving a distance of up to 1 km without line of sight.

## ⭐ When using this resource, please cite the original publication:
- [José M. Pereira Pontón, Verónica Ojeda, Víctor Asanza, Leandro L. Lorente-Leyva and Diego H. Peluffo-Ordóñez, “Design and Implementation of an IoT Control and Monitoring System for the Optimization of Shrimp Pools using LoRa Technology” International Journal of Advanced Computer Science and Applications(IJACSA), 14(8), 2023. http://dx.doi.org/10.14569/IJACSA.2023.0140829](https://thesai.org/Publications/ViewPaper?Volume=14&Issue=8&Code=IJACSA&SerialNo=29)

## IoT Architecture
An IoT architecture allows interconnection and communication between different devices by establishing a connection with the cloud. It is not necessary for the devices to be physically located in the same place; instead, the monitoring and visualization of various processes can be done from different platforms [24]. In a shrimp farm where access to technology is challenging, implementing IoT architecture concepts offers many advantages and benefits. Fig. 1 illustrates the characteristics that these services provide.
![image](https://github.com/josep5097/LoRa-Shrimp-Monitoring-Control/assets/12642226/c821ff96-ee19-41d2-974d-a81b8e41dae0)

## MATERIALS AND METHODS
LoRa communications can be modified and depend on different parameters, which can be configured in the application. These parameters include spreading factor, coding rate, transmission power, chirp polarity, and synchronization word. Due to the versatility LoRa offers in device-to-device transmission, it has been selected as the communication method for the study. The LoRa protocol will be used for intercommunication between the different nodes in the pools. Meanwhile, the internet module will be used in the gateway module for communication with the ThingSpeak platform, enabling real-time visualization of the abiotic parameters of the different pools, as shown in Fig. 3.
![image](https://github.com/josep5097/LoRa-Shrimp-Monitoring-Control/assets/12642226/79c73111-f353-44a6-864f-5ec3df1d3a38)

## Control
In the process control field, there are different techniques for implementation, and one common type of controller is the PID controller, which provides a fast dynamic response. However, it requires control calibration for events with high precision, and one of its disadvantages is its high sensitivity to noise. An alternative control type is fuzzy logic, which consists of two stages: fuzzification and defuzzification (see Fig. 4).
![image](https://github.com/josep5097/LoRa-Shrimp-Monitoring-Control/assets/12642226/542cff25-0d64-4c59-ae8f-6c65f1b5af02)

## Solution Description
For the monitoring and control of shrimp pools, the solution consists of a stage of measuring the abiotic parameters in the pond using a sensor node. Once the data is obtained, it is sent to a gateway node where it is processed using a fuzzy logic algorithm. This algorithm is designed to determine the next state of the pond's aerator (on or off). This value is then sent to an actuator node, which commands the activation of the aerator using a relay. A brief description of the process is shown in Fig. 12.
![image](https://github.com/josep5097/LoRa-Shrimp-Monitoring-Control/assets/12642226/e14b0f58-2b51-49e1-b655-cebc79f6038d)
Within the link layer, there are sensor nodes and actuator nodes, and communication between the devices is through the LoRa protocol. When using the LoRa communication protocol, a topology must be chosen for the communication between devices. For the present system, a star network topology was selected over a mesh network. This decision was made because devices in a full duplex communication (mesh) require being powered on all the time, leading to a higher energy demand. An outline of the established architecture is shown in Fig. 14.
![image](https://github.com/josep5097/LoRa-Shrimp-Monitoring-Control/assets/12642226/64b9e83c-62d6-4dfc-9c89-bf6903420306)
The captured data from the pools is visualized using the ThingSpeak platform, with the information being sent from the gateway device as described in Fig. 15.
![image](https://github.com/josep5097/LoRa-Shrimp-Monitoring-Control/assets/12642226/af542bc2-dc3a-4f0e-b4dd-6e1c41663965)
In Fig. 15, besides the formation of the JSON object that is sent, you can see the pins used to connect both the OLED and the LoRa module. Similarly, the connection used with the sensor and actuator nodes is described. For the sensor node, GPIO pins are used for the dissolved oxygen and temperature sensors, as shown in Fig. 16.
![image](https://github.com/josep5097/LoRa-Shrimp-Monitoring-Control/assets/12642226/df5ad182-4b6d-432b-9a37-54a4c95e913e)
Meanwhile, for the actuator nodes, a GPIO pin is used to activate a relay for turning on or off an aerator (see Fig. 17).
![image](https://github.com/josep5097/LoRa-Shrimp-Monitoring-Control/assets/12642226/5b219865-0dc4-48cb-a0a1-d0d9466fb968)

## RESULTS
The fuzzy rules used in this study were based on previous research [12], [13], [21]. From these established fuzzy rules, LabVIEW software was used to generate the fuzzy relation function, which reflects the expected behavior of the system. The fuzzy relation function was constructed based on the 12 defined fuzzy rules, and its response is shown in Fig. 28.
![image](https://github.com/josep5097/LoRa-Shrimp-Monitoring-Control/assets/12642226/0438b0d6-1694-42f5-ab97-35596fb64200)
The fuzzy system implemented in the embedded system achieves the performance demonstrated in Fig. 29. The interaction of the abiotic parameters with the mechanical movement of the aerator can be observed. The goal is that when the abiotic parameters are within an optimal range, the aerator switches to an off state.
![image](https://github.com/josep5097/LoRa-Shrimp-Monitoring-Control/assets/12642226/f5b559b8-aacc-4f56-9b68-1f4936e2bb7f)

## REFERENCES
- [1] Instituto Nacional de Pesca (INP), Estadísticas Acuícolas de Ecuador: Informe Anual 2020, Quito, Ecuador, 2021.
- [2] CEDIA, “Innovando el sector productivo,” vol. 6, 2021.
- [3] S. D. Rana, and S. Rani, “Fuzzy logic based control system for fresh water aquaculture: A MATLAB based simulation approach,” Serbian journal of electrical engineering, vol. 12, no 2, pp. 171-182, 2015.
- [4] K. Yue, and Y. Shen, “An overview of disruptive technologies for aquaculture,” Aquaculture and Fisheries, vol. 7, no. 2, pp. 111-120, 2022.
- [5] H. C. Li, K. W. Yu, C. H. Lien, C. Lin, C. R. Yu, and S. Vaidyanathan, “Improving Aquaculture Water Quality Using Dual-Input Fuzzy Logic Control for Ammonia Nitrogen Management,” Journal of Marine Science and Engineering, vol. 11, no. 6, 1109, 2023.
- [6] K. L. Tsai, L. W. Chen, L. J. Yang, H. J. Shiu, and H. W. Chen, “IoT based smart aquaculture system with automatic aerating and water quality monitoring,” Journal of Internet Technology, vol. 23, no. 1, pp. 177-184, 2022.
- [7] M. Li, C. Lin, J. Ren, and F. Jiang, F, “A wireless ecological aquaculture water quality monitoring system based on LoRa technology,” 2019 International Conference on Wireless Communication, Network and Multimedia Engineering (WCNME 2019), pp. 5-7, Atlantis Press, 2019.
- [8] H. Bates, M. Pierce, and A. Benter, “Real-time environmental monitoring for aquaculture using a LoRaWAN-based IoT sensor network,” Sensors, vol. 21, no. 23, 7963, 2021.
- [9] S. -T. Chen, S. -S. Lin, C. -W. Lan and T. -I. Chou, "Design and development of a LoRa based Water Quality Monitoring System," 2021 International Symposium on Intelligent Signal Processing and Communication Systems (ISPACS), Hualien City, Taiwan, 2021, pp. 1-2.
- [10] J. Pereira, M. Mora, and W. Agila, “Qualitative Model to Maximize Shrimp Growth at Low Cost." 2021 IEEE Fifth Ecuador Technical Chapters Meeting (ETCM). IEEE, pp. 1-7, 2021.
- [11] N. Peña-Navarro, and A. Varela-Mejías, A, “Prevalencia de las principales enfermedades infecciosas en el camarón blanco Penaeus vannamei cultivado en el Golfo de Nicoya, Costa Rica,” Revista de biología marina y oceanografía, vol. 51, no. 3, pp. 553-564, 2016.
- [12] J. J. Carbajal-Hernández, L. P. Sánchez-Fernández, J. A. Carrasco-Ochoa, and J. F. Martínez-Trinidad, “Immediate water quality assessment in shrimp culture using fuzzy inference systems,” Expert Syst. Appl., vol. 39, no. 12, pp. 10571–10582, 2012.
- [13] J. J. Carbajal-Hernández, L. P. Sánchez-Fernández, L. A. Villa-Vargas, J. A. Carrasco-Ochoa, and J. F. Martínez-Trinidad, “Water quality assessment in shrimp culture using an analytical hierarchical process,” Ecol. Indic., vol. 29, pp. 148–158, 2013.
- [14] N. C. Ferreira, C. Bonetti, and W. Q. Seiffert, “Hydrological and Water Quality Indices as management tools in marine shrimp culture,” Aquaculture, vol. 318, no. 3–4, pp. 425–433, 2011.
- [15] M. Salah Uddin, M. Fatin Istiaq, M. Rasadin, and M. Ruhel Talukder, “Freshwater shrimp farm monitoring system for Bangladesh based on internet of things,” Eng. Reports, vol. 2, no. 7, pp. 1–14, 2020.
- [16] C. E. Boyd, “Water quality in warmwater fish pond,” Agric. Exp., p. 359, 1990.
- [17] B. H. Lam, H. X. Huynh, M. Traoré, P. Y. Lucas, and B. Pottier, “Monitoring environmental factors in mekong delta of vietnam using wireless sensor network approach,” 8th Int. Conf. Simul. Model. Food Bio-Industry 2014, FOODSIM 2014, no. June, pp. 71–78, 2014.
- [18] N. C. Ferreira, “Aplicação de Índices de Qualidade de Água (IQA) como apoio à carcinicultura marinha,” Ufsc, p. 62, 2009.
- [19] R. E. Yambay-Rueda and E. M. Alvarez-Alvarado, “Cultivo intensivo de camarón blanco litopenaeus vannamei en sistemas cerrados de recirculacion.,” Universidad de Guayaquil, 2017.
- [20] M. G. Frías-Espericueta, M. Aguilar-Juárez, I. Osuna-López, S. Abad-Rosales, G. Izaguirre-Fierro, and D. Voltolina, “Los metales y la camaronicultura en México,” Hidrobiologica, vol. 21, no. 3, pp. 217–228, 2011.
- [21] K. Agustianto, T. Kustiari, P. Destarianto, and I. G. Wiryawan, “Development of realtime surface modeling vehicle for shrimp ponds (ReSMeV-SP),” IOP Conf. Ser. Earth Environ. Sci., vol. 672, no. 1, 2021.
- [22] R. A. Bórquez-Lopez, R. Casillas-Hernandez, J. A. Lopez-Elias, R. H. Barraza-Guardado, and L. R. Martinez-Cordova, “Improving feeding strategies for shrimp farming using fuzzy logic, based on water quality parameters,” Aquac. Eng., vol. 81, no. May, pp. 38–45, 2018.
- [23] J. B. Darodes de Tailly, J. Keitel, M. A. G. Owen, J. M. Alcaraz-Calero, M. E. Alexander, and K. A. Sloman, “Monitoring methods of feeding behaviour to answer key questions in penaeid shrimp feeding,” Rev. Aquac., vol. 13, no. 4, pp. 1828–1843, 2021.
- [24] C. Encinas, E. Ruiz, J. Cortez, and A. Espinoza, “ Design and implementation of a distributed IoT system for the monitoring of water quality in aquaculture,” In 2017 Wireless telecommunications symposium (WTS), pp. 1-7, IEEE, 2017.
- [25] B. S. Chaudhari, M. Zennaro, and S. Borkar, “LPWAN technologies: Emerging application characteristics, requirements, and design considerations,” Futur. Internet, vol. 12, no. 3, 2020.
- [26] T. G. Durand, L. Visagie, and M. J. Booysen, “Evaluation of next-generation low-power communication technology to replace GSM in IoT-applications,” IET Commun., vol. 13, no. 16, pp. 2533–2540, 2019.
- [27] LoRa Alliance, “LoRa and LoRaWAN: Technical overview | DEVELOPER PORTAL.” https://lora-developers.semtech.com/documentation/tech-papers-and-guides/lora-and-lorawan/ (accessed Jun. 12, 2022).
- [28] Sigfox, “Technology | Sigfox.” https://www.sigfox.com/en/what-sigfox/technology#id_security (accessed Feb. 12, 2022).
- [29] S. Farahani, “ZigBee/IEEE 802.15.4 Networking Examples,” ZigBee Wirel. Networks Transceivers, pp. 25–32, 2008.
- [30] NXP, “Maximizing security in zigbee networks,” 2017, [Online]. Available: https://www.nxp.com/docs/en/supporting-information/MAXSECZBNETART.pdf.
- [31] E. Aras, G. S. Ramachandran, P. Lawrence, and D. Hughes, “Exploring the security vulnerabilities of LoRa,” 2017 3rd IEEE Int. Conf. Cybern. CYBCONF 2017 - Proc., no. June, 2017.
