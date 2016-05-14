package entity
{
	import mx.collections.ArrayCollection;

	public class Util
	{
		public static function combine(arr:ArrayCollection):String
		{
			var result:String = "";
			for (var i:int = 0; i < arr.length; ++i) {
				var isFirst:Boolean = true;
				if (isFirst) {
					result = arr[i];
					isFirst = false;
				} else {
					result += ","+arr[i];
				}
			}
			
			return result;
		}
	}
}