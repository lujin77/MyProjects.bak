/**
 * This is a generated class and is not intended for modification.  To customize behavior
 * of this value object you may modify the generated sub-class of this class - User.as.
 */

package valueObjects
{
import com.adobe.fiber.services.IFiberManagingService;
import com.adobe.fiber.valueobjects.IValueObject;
import flash.events.EventDispatcher;
import mx.collections.ArrayCollection;
import mx.events.PropertyChangeEvent;

import flash.net.registerClassAlias;
import flash.net.getClassByAlias;
import com.adobe.fiber.core.model_internal;
import com.adobe.fiber.valueobjects.IPropertyIterator;
import com.adobe.fiber.valueobjects.AvailablePropertyIterator;

use namespace model_internal;

[ExcludeClass]
public class _Super_User extends flash.events.EventDispatcher implements com.adobe.fiber.valueobjects.IValueObject
{
    model_internal static function initRemoteClassAliasSingle(cz:Class) : void
    {
    }

    model_internal static function initRemoteClassAliasAllRelated() : void
    {
    }

    model_internal var _dminternal_model : _UserEntityMetadata;
    model_internal var _changedObjects:mx.collections.ArrayCollection = new ArrayCollection();

    public function getChangedObjects() : Array
    {
        _changedObjects.addItemAt(this,0);
        return _changedObjects.source;
    }

    public function clearChangedObjects() : void
    {
        _changedObjects.removeAll();
    }

    /**
     * properties
     */
    private var _internal_id : String;
    private var _internal_userid : String;
    private var _internal_psw : String;
    private var _internal_name : String;
    private var _internal_sex : String;
    private var _internal_mobile : String;
    private var _internal_tel : String;
    private var _internal_qq : String;
    private var _internal_email : String;
    private var _internal_com_name : String;
    private var _internal_com_addr : String;
    private var _internal_state : String;
    private var _internal_level : String;
    private var _internal_sms : int;
    private var _internal_msms : int;
    private var _internal_reply : int;
    private var _internal_manager_id : String;
    private var _internal_sms_sign : String;

    private static var emptyArray:Array = new Array();


    /**
     * derived property cache initialization
     */
    model_internal var _cacheInitialized_isValid:Boolean = false;

    model_internal var _changeWatcherArray:Array = new Array();

    public function _Super_User()
    {
        _model = new _UserEntityMetadata(this);

        // Bind to own data or source properties for cache invalidation triggering

    }

    /**
     * data/source property getters
     */

    [Bindable(event="propertyChange")]
    public function get id() : String
    {
        return _internal_id;
    }

    [Bindable(event="propertyChange")]
    public function get userid() : String
    {
        return _internal_userid;
    }

    [Bindable(event="propertyChange")]
    public function get psw() : String
    {
        return _internal_psw;
    }

    [Bindable(event="propertyChange")]
    public function get name() : String
    {
        return _internal_name;
    }

    [Bindable(event="propertyChange")]
    public function get sex() : String
    {
        return _internal_sex;
    }

    [Bindable(event="propertyChange")]
    public function get mobile() : String
    {
        return _internal_mobile;
    }

    [Bindable(event="propertyChange")]
    public function get tel() : String
    {
        return _internal_tel;
    }

    [Bindable(event="propertyChange")]
    public function get qq() : String
    {
        return _internal_qq;
    }

    [Bindable(event="propertyChange")]
    public function get email() : String
    {
        return _internal_email;
    }

    [Bindable(event="propertyChange")]
    public function get com_name() : String
    {
        return _internal_com_name;
    }

    [Bindable(event="propertyChange")]
    public function get com_addr() : String
    {
        return _internal_com_addr;
    }

    [Bindable(event="propertyChange")]
    public function get state() : String
    {
        return _internal_state;
    }

    [Bindable(event="propertyChange")]
    public function get level() : String
    {
        return _internal_level;
    }

    [Bindable(event="propertyChange")]
    public function get sms() : int
    {
        return _internal_sms;
    }

    [Bindable(event="propertyChange")]
    public function get msms() : int
    {
        return _internal_msms;
    }

    [Bindable(event="propertyChange")]
    public function get reply() : int
    {
        return _internal_reply;
    }

    [Bindable(event="propertyChange")]
    public function get manager_id() : String
    {
        return _internal_manager_id;
    }

    [Bindable(event="propertyChange")]
    public function get sms_sign() : String
    {
        return _internal_sms_sign;
    }

    public function clearAssociations() : void
    {
    }

    /**
     * data/source property setters
     */

    public function set id(value:String) : void
    {
        var oldValue:String = _internal_id;
        if (oldValue !== value)
        {
            _internal_id = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "id", oldValue, _internal_id));
        }
    }

    public function set userid(value:String) : void
    {
        var oldValue:String = _internal_userid;
        if (oldValue !== value)
        {
            _internal_userid = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "userid", oldValue, _internal_userid));
        }
    }

    public function set psw(value:String) : void
    {
        var oldValue:String = _internal_psw;
        if (oldValue !== value)
        {
            _internal_psw = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "psw", oldValue, _internal_psw));
        }
    }

    public function set name(value:String) : void
    {
        var oldValue:String = _internal_name;
        if (oldValue !== value)
        {
            _internal_name = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "name", oldValue, _internal_name));
        }
    }

    public function set sex(value:String) : void
    {
        var oldValue:String = _internal_sex;
        if (oldValue !== value)
        {
            _internal_sex = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "sex", oldValue, _internal_sex));
        }
    }

    public function set mobile(value:String) : void
    {
        var oldValue:String = _internal_mobile;
        if (oldValue !== value)
        {
            _internal_mobile = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "mobile", oldValue, _internal_mobile));
        }
    }

    public function set tel(value:String) : void
    {
        var oldValue:String = _internal_tel;
        if (oldValue !== value)
        {
            _internal_tel = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "tel", oldValue, _internal_tel));
        }
    }

    public function set qq(value:String) : void
    {
        var oldValue:String = _internal_qq;
        if (oldValue !== value)
        {
            _internal_qq = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "qq", oldValue, _internal_qq));
        }
    }

    public function set email(value:String) : void
    {
        var oldValue:String = _internal_email;
        if (oldValue !== value)
        {
            _internal_email = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "email", oldValue, _internal_email));
        }
    }

    public function set com_name(value:String) : void
    {
        var oldValue:String = _internal_com_name;
        if (oldValue !== value)
        {
            _internal_com_name = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "com_name", oldValue, _internal_com_name));
        }
    }

    public function set com_addr(value:String) : void
    {
        var oldValue:String = _internal_com_addr;
        if (oldValue !== value)
        {
            _internal_com_addr = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "com_addr", oldValue, _internal_com_addr));
        }
    }

    public function set state(value:String) : void
    {
        var oldValue:String = _internal_state;
        if (oldValue !== value)
        {
            _internal_state = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "state", oldValue, _internal_state));
        }
    }

    public function set level(value:String) : void
    {
        var oldValue:String = _internal_level;
        if (oldValue !== value)
        {
            _internal_level = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "level", oldValue, _internal_level));
        }
    }

    public function set sms(value:int) : void
    {
        var oldValue:int = _internal_sms;
        if (oldValue !== value)
        {
            _internal_sms = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "sms", oldValue, _internal_sms));
        }
    }

    public function set msms(value:int) : void
    {
        var oldValue:int = _internal_msms;
        if (oldValue !== value)
        {
            _internal_msms = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "msms", oldValue, _internal_msms));
        }
    }

    public function set reply(value:int) : void
    {
        var oldValue:int = _internal_reply;
        if (oldValue !== value)
        {
            _internal_reply = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "reply", oldValue, _internal_reply));
        }
    }

    public function set manager_id(value:String) : void
    {
        var oldValue:String = _internal_manager_id;
        if (oldValue !== value)
        {
            _internal_manager_id = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "manager_id", oldValue, _internal_manager_id));
        }
    }

    public function set sms_sign(value:String) : void
    {
        var oldValue:String = _internal_sms_sign;
        if (oldValue !== value)
        {
            _internal_sms_sign = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "sms_sign", oldValue, _internal_sms_sign));
        }
    }

    /**
     * Data/source property setter listeners
     *
     * Each data property whose value affects other properties or the validity of the entity
     * needs to invalidate all previously calculated artifacts. These include:
     *  - any derived properties or constraints that reference the given data property.
     *  - any availability guards (variant expressions) that reference the given data property.
     *  - any style validations, message tokens or guards that reference the given data property.
     *  - the validity of the property (and the containing entity) if the given data property has a length restriction.
     *  - the validity of the property (and the containing entity) if the given data property is required.
     */


    /**
     * valid related derived properties
     */
    model_internal var _isValid : Boolean;
    model_internal var _invalidConstraints:Array = new Array();
    model_internal var _validationFailureMessages:Array = new Array();

    /**
     * derived property calculators
     */

    /**
     * isValid calculator
     */
    model_internal function calculateIsValid():Boolean
    {
        var violatedConsts:Array = new Array();
        var validationFailureMessages:Array = new Array();

        var propertyValidity:Boolean = true;

        model_internal::_cacheInitialized_isValid = true;
        model_internal::invalidConstraints_der = violatedConsts;
        model_internal::validationFailureMessages_der = validationFailureMessages;
        return violatedConsts.length == 0 && propertyValidity;
    }

    /**
     * derived property setters
     */

    model_internal function set isValid_der(value:Boolean) : void
    {
        var oldValue:Boolean = model_internal::_isValid;
        if (oldValue !== value)
        {
            model_internal::_isValid = value;
            _model.model_internal::fireChangeEvent("isValid", oldValue, model_internal::_isValid);
        }
    }

    /**
     * derived property getters
     */

    [Transient]
    [Bindable(event="propertyChange")]
    public function get _model() : _UserEntityMetadata
    {
        return model_internal::_dminternal_model;
    }

    public function set _model(value : _UserEntityMetadata) : void
    {
        var oldValue : _UserEntityMetadata = model_internal::_dminternal_model;
        if (oldValue !== value)
        {
            model_internal::_dminternal_model = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "_model", oldValue, model_internal::_dminternal_model));
        }
    }

    /**
     * methods
     */


    /**
     *  services
     */
    private var _managingService:com.adobe.fiber.services.IFiberManagingService;

    public function set managingService(managingService:com.adobe.fiber.services.IFiberManagingService):void
    {
        _managingService = managingService;
    }

    model_internal function set invalidConstraints_der(value:Array) : void
    {
        var oldValue:Array = model_internal::_invalidConstraints;
        // avoid firing the event when old and new value are different empty arrays
        if (oldValue !== value && (oldValue.length > 0 || value.length > 0))
        {
            model_internal::_invalidConstraints = value;
            _model.model_internal::fireChangeEvent("invalidConstraints", oldValue, model_internal::_invalidConstraints);
        }
    }

    model_internal function set validationFailureMessages_der(value:Array) : void
    {
        var oldValue:Array = model_internal::_validationFailureMessages;
        // avoid firing the event when old and new value are different empty arrays
        if (oldValue !== value && (oldValue.length > 0 || value.length > 0))
        {
            model_internal::_validationFailureMessages = value;
            _model.model_internal::fireChangeEvent("validationFailureMessages", oldValue, model_internal::_validationFailureMessages);
        }
    }


}

}
