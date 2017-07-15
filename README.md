# Towers Of Madness  
  
Copyright 2017 Daniel Barbosa, Francisco Anderson Bezerra Rodrigues, Gabriel Barbosa, Marcelo Bulhões, Vitor Silva de Deus, Mariana Pannuzio, Bruno Gomes e Luiz Bastos  
  
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
-----------------------

**Towers of Madness** é um tower defense no qual você deve proteger os últimos estudantes saudáveis da UnB de um Mal que foi despertado e que está infectando alunos de diversos cursos.  
  
#### Objetivo do jogo:
Impedir que os infetados cheguem à reitoria e à biblioteca.

#### Controles:
- `W A S D` para movimentação da câmera  
- Rodinha do mouse para zoom  
- Botão direito do mouse para confirmar a posição das torres
- Botão esquerdo do mouse para interagir com a UI
- `[` para reduzir o volume da música e `]` para aumentar o volume da música  
- `,` para reduzir o volume dos efeitos sonoros e `.` para aumentar o volume dos efeitos sonoros.  
- `-` para reduzir o frame rate máximo em 5, e `=` para aumentar o frame rate máximo em 5  
  
#### Equipe de desenvolvimento:
- Programadores:
	- Daniel Barbosa
	- Francisco Anderson Bezerra Rodrigues
	- Gabriel Barbosa
	- Marcelo Bulhões
	- Vitor Silva de Deus
- Artistas:
	- Mariana Pannuzio
	- Bruno Gomes
- Músicos:
	- Luiz Bastos

---

#### Dependências:
- SDL2
- SDL2_mixer
- SDL2_TTF
- SDL2_image
- MingW **(Windows)**
- git lfs*

*O vídeo de gameplay do nosso jogo está nesse repositório. Como ele é grande (approx. 100 MB), clonar o repositório se tornou um processo demorado (e impossível porquê o git reclama de arquivos > 50 MB). Usamos então o git lfs para conseguir armazenar o vídeo e, caso desejado, pular o seu download ao fazer o clone.

**O download e instalação do git lfs somente se faz necessário se, e somente se, se deseje baixar o vídeo ao fazer o clone.** Se desejar fazer o download do vídeo pelo navegador, basta clicar para obter o raw dele.

*P.S.: Se você tiver o git lfs instalado e ***não*** quiser baixar o vídeo, terá que pular a etapa de smudge.*

Caso queira um lista mais completa, mas com dependẽncias que são utilizadas internamente pela própria SDL2 no Linux, a saída do ldd do jogo é:

		linux-vdso.so.1 (0x00007ffd83898000)  
		libSDL2-2.0.so.0 => /usr/lib/x86_64-linux-gnu/libSDL2-2.0.so.0 (0x00007fcc73a4f000)  
		libSDL2_image-2.0.so.0 => /usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so.0 (0x00007fcc7382c000)  
		libSDL2_mixer-2.0.so.0 => /usr/lib/x86_64-linux-gnu/libSDL2_mixer-2.0.so.0 (0x00007fcc735d8000)  
		libSDL2_ttf-2.0.so.0 => /usr/lib/x86_64-linux-gnu/libSDL2_ttf-2.0.so.0 (0x00007fcc733d0000)  
		libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fcc7304e000)  
		libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fcc72d48000)  
		libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fcc72b31000)  
		libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fcc72792000)  
		libasound.so.2 => /usr/lib/x86_64-linux-gnu/libasound.so.2 (0x00007fcc72485000)  
		libdl.so.2 => /lib/x86_64-linux-gnu/libdl.so.2 (0x00007fcc72281000)  
		libpulse-simple.so.0 => /usr/lib/x86_64-linux-gnu/libpulse-simple.so.0 (0x00007fcc7207c000)  
		libpulse.so.0 => /usr/lib/x86_64-linux-gnu/libpulse.so.0 (0x00007fcc71e29000)  
		libsndio.so.6.1 => /usr/lib/x86_64-linux-gnu/libsndio.so.6.1 (0x00007fcc71c19000)  
		libX11.so.6 => /usr/lib/x86_64-linux-gnu/libX11.so.6 (0x00007fcc718d9000)  
		libXext.so.6 => /usr/lib/x86_64-linux-gnu/libXext.so.6 (0x00007fcc716c7000)  
		libXcursor.so.1 => /usr/lib/x86_64-linux-gnu/libXcursor.so.1 (0x00007fcc714bc000)  
		libXinerama.so.1 => /usr/lib/x86_64-linux-gnu/libXinerama.so.1 (0x00007fcc712b9000)  
		libXi.so.6 => /usr/lib/x86_64-linux-gnu/libXi.so.6 (0x00007fcc710a7000)  
		libXrandr.so.2 => /usr/lib/x86_64-linux-gnu/libXrandr.so.2 (0x00007fcc70e9c000)  
		libXss.so.1 => /usr/lib/x86_64-linux-gnu/libXss.so.1 (0x00007fcc70c99000)  
		libXxf86vm.so.1 => /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1 (0x00007fcc70a93000)  
		libwayland-egl.so.1 => /usr/lib/x86_64-linux-gnu/libwayland-egl.so.1 (0x00007fcc70891000)  
		libwayland-client.so.0 => /usr/lib/x86_64-linux-gnu/libwayland-client.so.0 (0x00007fcc70682000)  
		libwayland-cursor.so.0 => /usr/lib/x86_64-linux-gnu/libwayland-cursor.so.0 (0x00007fcc70478000)  
		libxkbcommon.so.0 => /usr/lib/x86_64-linux-gnu/libxkbcommon.so.0 (0x00007fcc70238000)  
		libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007fcc7001b000)  
		librt.so.1 => /lib/x86_64-linux-gnu/librt.so.1 (0x00007fcc6fe13000)  
		libpng16.so.16 => /usr/lib/x86_64-linux-gnu/libpng16.so.16 (0x00007fcc6fbe0000)  
		libjpeg.so.62 => /usr/lib/x86_64-linux-gnu/libjpeg.so.62 (0x00007fcc6f975000)  
		libtiff.so.5 => /usr/lib/x86_64-linux-gnu/libtiff.so.5 (0x00007fcc6f6fc000)  
		libwebp.so.6 => /usr/lib/x86_64-linux-gnu/libwebp.so.6 (0x00007fcc6f49b000)  
		libmodplug.so.1 => /usr/lib/x86_64-linux-gnu/libmodplug.so.1 (0x00007fcc6f10e000)  
		libfluidsynth.so.1 => /usr/lib/x86_64-linux-gnu/libfluidsynth.so.1 (0x00007fcc6ee45000)  
		libvorbisfile.so.3 => /usr/lib/x86_64-linux-gnu/libvorbisfile.so.3 (0x00007fcc6ec3c000)  
		libFLAC.so.8 => /usr/lib/x86_64-linux-gnu/libFLAC.so.8 (0x00007fcc6e9c5000)  
		libmad.so.0 => /usr/lib/x86_64-linux-gnu/libmad.so.0 (0x00007fcc6e7a3000)  
		libfreetype.so.6 => /usr/lib/x86_64-linux-gnu/libfreetype.so.6 (0x00007fcc6e4ee000)  
		/lib64/ld-linux-x86-64.so.2 (0x0000564e53b76000)  
		libpulsecommon-10.0.so => /usr/lib/x86_64-linux-gnu/pulseaudio/libpulsecommon-10.0.so (0x00007fcc6e26b000)  
		libcap.so.2 => /lib/x86_64-linux-gnu/libcap.so.2 (0x00007fcc6e065000)  
		libdbus-1.so.3 => /lib/x86_64-linux-gnu/libdbus-1.so.3 (0x00007fcc6de15000)  
		libbsd.so.0 => /lib/x86_64-linux-gnu/libbsd.so.0 (0x00007fcc6dbfe000)  
		libxcb.so.1 => /usr/lib/x86_64-linux-gnu/libxcb.so.1 (0x00007fcc6d9d6000)  
		libXrender.so.1 => /usr/lib/x86_64-linux-gnu/libXrender.so.1 (0x00007fcc6d7cc000)  
		libXfixes.so.3 => /usr/lib/x86_64-linux-gnu/libXfixes.so.3 (0x00007fcc6d5c6000)  
		libffi.so.6 => /usr/lib/x86_64-linux-gnu/libffi.so.6 (0x00007fcc6d3bd000)  
		libz.so.1 => /lib/x86_64-linux-gnu/libz.so.1 (0x00007fcc6d1a1000)  
		liblzma.so.5 => /lib/x86_64-linux-gnu/liblzma.so.5 (0x00007fcc6cf7b000)  
		libjbig.so.0 => /usr/lib/x86_64-linux-gnu/libjbig.so.0 (0x00007fcc6cd6d000)  
		libglib-2.0.so.0 => /lib/x86_64-linux-gnu/libglib-2.0.so.0 (0x00007fcc6ca59000)  
		libjack.so.0 => /usr/lib/x86_64-linux-gnu/libjack.so.0 (0x00007fcc6c812000)  
		libsndfile.so.1 => /usr/lib/x86_64-linux-gnu/libsndfile.so.1 (0x00007fcc6c59a000)  
		libreadline.so.7 => /lib/x86_64-linux-gnu/libreadline.so.7 (0x00007fcc6c34b000)  
		libvorbis.so.0 => /usr/lib/x86_64-linux-gnu/libvorbis.so.0 (0x00007fcc6c11f000)  
		libogg.so.0 => /usr/lib/x86_64-linux-gnu/libogg.so.0 (0x00007fcc6bf16000)  
		libX11-xcb.so.1 => /usr/lib/x86_64-linux-gnu/libX11-xcb.so.1 (0x00007fcc6bd14000)  
		libICE.so.6 => /usr/lib/x86_64-linux-gnu/libICE.so.6 (0x00007fcc6baf7000)  
		libSM.so.6 => /usr/lib/x86_64-linux-gnu/libSM.so.6 (0x00007fcc6b8ef000)  
		libXtst.so.6 => /usr/lib/x86_64-linux-gnu/libXtst.so.6 (0x00007fcc6b6e7000)  
		libsystemd.so.0 => /lib/x86_64-linux-gnu/libsystemd.so.0 (0x00007fcc6b65c000)  
		libwrap.so.0 => /lib/x86_64-linux-gnu/libwrap.so.0 (0x00007fcc6b452000)  
		libasyncns.so.0 => /usr/lib/x86_64-linux-gnu/libasyncns.so.0 (0x00007fcc6b24c000)  
		libXau.so.6 => /usr/lib/x86_64-linux-gnu/libXau.so.6 (0x00007fcc6b048000)  
		libXdmcp.so.6 => /usr/lib/x86_64-linux-gnu/libXdmcp.so.6 (0x00007fcc6ae42000)  
		libpcre.so.3 => /lib/x86_64-linux-gnu/libpcre.so.3 (0x00007fcc6abcd000)  
		libopus.so.0 => /usr/lib/x86_64-linux-gnu/libopus.so.0 (0x00007fcc6a97e000)  
		libvorbisenc.so.2 => /usr/lib/x86_64-linux-gnu/libvorbisenc.so.2 (0x00007fcc6a6d5000)  
		libtinfo.so.5 => /lib/x86_64-linux-gnu/libtinfo.so.5 (0x00007fcc6a4ab000)  
		libuuid.so.1 => /lib/x86_64-linux-gnu/libuuid.so.1 (0x00007fcc6a2a6000)  
		libselinux.so.1 => /lib/x86_64-linux-gnu/libselinux.so.1 (0x00007fcc6a07c000)  
		liblz4.so.1 => /usr/lib/x86_64-linux-gnu/liblz4.so.1 (0x00007fcc69e6a000)  
		libgcrypt.so.20 => /lib/x86_64-linux-gnu/libgcrypt.so.20 (0x00007fcc69b5b000)  
		libnsl.so.1 => /lib/x86_64-linux-gnu/libnsl.so.1 (0x00007fcc69943000)  
		libresolv.so.2 => /lib/x86_64-linux-gnu/libresolv.so.2 (0x00007fcc6972c000)  
		libgpg-error.so.0 => /lib/x86_64-linux-gnu/libgpg-error.so.0 (0x00007fcc69515000)  
  
## Como compilar
**No linux:**
Após instalar as dependências, baixe o projeto no github e rode o comando:  

`make release`

O executável terá o nome JOGO

**No windows:**
Após instalar as dependências, baixe o projeto no github e rode o comando:

`mingw32-make release`

O executável terá o nome JOGO.exe

Esse jogo está sobre a licensa LGPL versão 3.0, escrita acima.
  
Screenshots do jogo podem ser vistas em: [https://unbgames.lappis.rocks/games/11/Towers%20of%20Madness](https://unbgames.lappis.rocks/games/11/Towers%20of%20Madness)

O gameplay pode ser visto em: [https://github.com/Anders1232/EngineIDJ/blob/master/Gameplay.mp4](https://github.com/Anders1232/EngineIDJ/blob/master/Gameplay.mp4)
  
  
Link para documentação doxygen: [https://anders1232.github.io/EngineIDJ](https://anders1232.github.io/EngineIDJ)
  
Acompanhamento do projeto: [https://github.com/Anders1232/EngineIDJ/projects/1](https://github.com/Anders1232/EngineIDJ/projects/1)

----------------

Sistema de uso do repositório (em adaptação):
- Branch dev saindo de master.  
- Um branch para cada feature saindo de dev. O branch será nomeado "feature/*" onde "*" será o nome da feature. Exemplo "feature/drag-n-drop".  
- Para juntar qualquer feature ao dev, será um pull request que deve ser revisado e testado por pelo menos um outro programador, ou seja, você nunca aceitará seus próprios pull requests. O branch será excluído assim que o pull request for aceito e realizado.  
- Se uma feature for complexa (por exemplo UI), vc pode fazer sub branches. Exemplo "feature/UI/animacao-telas". Todas as regras acima se aplicam.  
- Semanalmente, ou quinzenalmente, faríamos um merge do tweaks (descrito mais abaixo) pro master e depois do dev pro master, atualizando o número da versão minor. E depois um merge do master pro dev.  
- A documentação deve estar atualizada e refletindo com precisão o branch dev ANTES do merge ser feito.  
- Extremamente recomendável de que cada pull request de features já estejam com sua documentação correta.  
- Merges e pull requests só devem ser feitos se o código compilar e executar sem game-breaking bugs.  
- Branches de correção de bugs saem de master com nomenclatura "bugfix/*". Onde * é o número da issue no github. Exemplo "bugfix/32".  
- Branches de bugfix se juntam ao master da mesma forma que um de feature se junta ao dev. Mas atualizando a versão de patch.  
- Branches de adição ou grande alterações de arte/música serão em branches de feature, preferencialmente compostos de um único commit. Numeração de versão segue o mesmo padrão.  
- Tweaks será um branch saindo de master. Ele será feito de commits únicos que ajustam coisas. Tipo nome de arquivo de música, texto que aparece sei lá onde, etc.  
- O branch tweaks não receberá um merge do master toda vez, somente pela primeira vez que for ter um patch naquela versão. Cada commit altera o número da versão de patch.  
- A numeração de versão será semântico, ou seja, MAJOR.MINOR.PATCH.TWEAK . Qualquer atualização em um número zera todos os números à sua direita.  
- Commits DEVEM ter nomes (e, se aplicáveis, resumos) descritivos. Nada de "asdfgh" ou "teste", etc...  
- Se possível, colocar um resumo de tudo que foi alterado num pull request.  
- Entregáveis receberão etiquetas (tags) com o valor 30, 70 ou 100.  

