
#!/bin/bash

# Install required packages
sudo apt-get update
sudo apt-get install -y build-essential libsdl2-dev libsdl2-ttf-dev

# Download and install TTF library from source
wget https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.tar.gz
tar -zxvf SDL2_ttf-2.0.15.tar.gz
cd SDL2_ttf-2.0.15/
./configure && make && sudo make install
cd ..
rm -rf SDL2_ttf-2.0.15 SDL2_ttf-2.0.15.tar.gz

# Print installation success message
echo "SDL and TTF libraries installed successfully!"

