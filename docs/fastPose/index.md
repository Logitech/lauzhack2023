# Fastpose
​
Fastpose is an open source library that can perform a 2D/3D pose estimation in real time on a CPU.

​<img src="..\img\fastPose.gif"  style="max-width: 75%">
​
# Get Started
​
## Install the dependencies:
```
# create the environment
conda create -n fastpose python=3.6
​
# The both following packages are non-gpu apis
conda install -c conda-forge tensorflow
conda install pytorch torchvision -c pytorch
​
# older version of opencv can lead to error (version 3.4.2)
conda install opencv
​
conda install matplotlib
​
conda install requests
```
​
## Download the Project:
Download the [project source code](https://github.com/Drnoodle/fastpose) and the [parameter's archive](https://bitbucket.org/hugo_bonnome/fastpose_parameters/downloads/parameters.zip) that embeds the exported graph in .pb (protograph) as well as the training tensorflow checkpoints. When the download is completed, unzip the parameters in the project root's folder.
​
By default, the 2D inference is made with the tiny version, the medium version is not fully converged and its just a bit more accurate than the tiny one while decreasing the speed by more than a factor 2. This is why, without any extra work, the selected models do not have to be modified.
​
## Activate the environment
```
source activate fastpose
```
​
## Run Fastpose
**2D demo:** Launch the pose estimator by running demo_2d.py in the root folder of the project:
```
python demo_2d.py [webcam | path_to_video_file] max_person_threshold
```
​
**2D/3D demo:** Fastpose also provides a tiny backend working on the loopback to allow better compatibility with other programming languages. To use fastpose in localhost, start backend.py in the root folder of the project:
​
```
python backend.py port_number max_person_threshold
```
​
frontend_2d.py sends the image to the backend and displays the visualization while frontend_3d.html is a 3D visualization made in html (D3) that can display the 3D pose estimation performed over the video stream sent by frontend_2d.py.
​
**From an external server:** If you need to run the backend script on an external server this unix command redirects the annotation stream into your localhost ip on the port_frontend :
​
```
ssh -i ~/.ssh/server_private_key -f user@ip -L port_frontend:localhost:port_backend -N
```
​
​
For more more information, check out [this blog post](https://drnoodle.github.io/fastpose_html/) from the author.
