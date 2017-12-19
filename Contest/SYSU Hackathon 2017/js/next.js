function nextNew() {
  var blurFilter1 = new PIXI.filters.BlurFilter();

  app.stage.filters = [blurFilter1];

  var count = 0;

  // app.stage.removeChild(littleDudes);
  const myticker_next = new PIXI.ticker.Ticker();
  myticker_next.stop();
  myticker_next.add(function() {

    count += 0.005;

    var blurAmount = Math.cos(count);

    blurFilter1.blur = 20 * (blurAmount);
  });
  myticker_next.start();
  }

function nextDelete() {
  blurFilter1.blur = 0;
  myticker_next.stop();
}
