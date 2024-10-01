const canvas = document.getElementById('gamecanvas');

function goFullScreen() 
{
	if (canvas.requestFullscreen)
	{
		canvas.requestFullscreen();
	} 
	else if (canvas.mozRequestFullScreen)
	{
		canvas.mozRequestFullScreen();
	}
	else if (canvas.webkitRequestFullscreen)
	{
		canvas.webkitRequestFullscreen();
	}
	else if (canvas.msRequestFullscreen)
	{
		canvas.msRequestFullscreen();
	}
}

function resizeCanvas() 
{
	if (document.fullscreenElement || document.webkitFullscreenElement ||
		document.mozFullScreenElement || document.msFullscreenElement)
	{
		canvas.width = window.innerWidth;
		canvas.height = window.innerHeight;
	}
	else
	{
		canvas.width = 1280;
		canvas.height = 720;
	}
}

document.addEventListener('fullscreenchange', resizeCanvas);
document.addEventListener('webkitfullscreenchange', resizeCanvas);
document.addEventListener('mozfullscreenchange', resizeCanvas);
document.addEventListener('MSFullscreenChange', resizeCanvas);
