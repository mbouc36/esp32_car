# esp32_car
Small car using esp32 


Sample Development Workflow:
1. Activate docker container

Sample Upload Workflow
1. Ensure to be outside of docker container
2. Update `platformio_override.ini` with expected serial port
3. Create venv and install `pip install platformio`
4. Upload to device: `pio run -t upload`
