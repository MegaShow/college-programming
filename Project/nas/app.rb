require 'sinatra'
require 'haml'

get '/want' do
  haml :want
end

post '/want' do
  if params['val'].length != 0
    open 'want.txt', 'a+' do |f|
      f.puts params['userName'] + ' ' + params['val']
      @userName = params['userName']
      haml :success
    end
  else
    redirect '/want'
  end
end
