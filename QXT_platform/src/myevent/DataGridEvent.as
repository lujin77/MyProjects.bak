package myevent
{
	import flash.events.Event;
	public class DataGridEvent extends Event
	{
		public var isSelect:Boolean;
		public var o:Object;
		public function DataGridEvent(_o:Object,_isSelect:Boolean):void
		{
			o = _o;
			isSelect = _isSelect;
			super("selectRow", true, false);
		}

	}
}