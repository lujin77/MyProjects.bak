package event.util
{
	import flash.events.Event;
	
	public class Back2HomeEvent extends Event
	{
		public static const BACK2HOME_EVENT:String = "Back2HomeEvent";  
		
		public function Back2HomeEvent(type:String, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(type, bubbles, cancelable);
		}
		
		override public function clone():Event{  
			return new Back2HomeEvent(type,bubbles,cancelable);  
		}
	}
}